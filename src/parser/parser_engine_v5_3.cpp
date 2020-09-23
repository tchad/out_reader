
#include <iostream>
#include <cstdlib>
#include <unordered_set>

#include <parser/include/parser_engine_v5_3.h>


namespace reader {
    ParserStatus ParserEngineV53::Parse(std::ifstream &fs, DatasetV53 *dset)
    {
        /*
         * Executes in two stages:
         * Stage 1 header
         * Stage 2 data
         *
         * Stage 1 Read all header sections, if anything except index
         *         is duplicated then error. Once independent variable is detected
         *         stage 2 begins. 
         * Stage 2 No element from the header can occur anymore at this point.
         *         Read record by record and return error if non existing index occurs.
         *
         * Final check Verify that every record contains all indexex. Sort the list by time,
         * Reading record. Once independent variable is encountered keep constructing the record
         * When next independent variable occurs add record to dataset and start new record object.
         */

        std::string line;
        std::smatch match;
        std::unordered_set<std::uint32_t> hashtable;
        SegmentType segment_type;

#ifdef __READER_PARSER_ENGINE_V5_3_DEBUG__
        std::clog << ENGINE_NAME << std::endl;
#endif

        bool stage1 = true;
        bool time_resolution_read = false;
        bool hier_separator_read = false;
        DatasetV53::Record record_tmp;

        while (!fs.eof()) {
            std::getline(fs, line);  
            segment_type = ParseLine(line, match);

            switch(segment_type) {
                case TIME_RESOLUTION:
                    if (!stage1 || time_resolution_read) {
                        return ParserStatus::ERR_WRONG_FILE_CONTENT;
                    } else {
                        time_resolution_read = true;
                        dset->time_resolution = match.str(1);
                    }
                    break;
                case HIER_SEPARATION:
                    if (!stage1 || hier_separator_read) {
                        return ParserStatus::ERR_WRONG_FILE_CONTENT;
                    } else {
                        hier_separator_read = true;
                        dset->hier_separation = match.str(1);
                    }
                    break;
                case INDEX:
                    if (!stage1) {
                        return ParserStatus::ERR_WRONG_FILE_CONTENT;
                    } else {
                        //check for duplicates
                        int tmp = std::atoi(match.str(2).c_str());

                        /*
                         * Fail if
                         * index negative
                         * or index definition already present
                         */

                        if (tmp < 0 || dset->index_map.contains(tmp)) {
                            return ParserStatus::ERR_WRONG_FILE_CONTENT;
                        }

                        //DatasetV53::Index index{DatasetV53::IdxId(tmp), match.str(1), match.str(3)};
                        //dset->index_map[tmp] = index;
                        dset->index_map[tmp] = DatasetV53::Index{DatasetV53::IdxId(tmp), match.str(1), match.str(3)};
                    }
                    break;
                case VAR_INDEPENDENT:
                    if (!stage1) {
                        //Save record if already in stage 2 which means there is valid data present
                        dset->data.push_back(record_tmp);
                    } else {
                        //transition to stage 2
                        stage1 = false;
                    }
                    //Initialize clean working object 
                    record_tmp = DatasetV53::Record();

                    //Process
                    {
                        int tmp = std::atoi(match.str(1).c_str());
                        static int g = 10000;

                        if(tmp > g) {
                            g += 100000;
                            std::clog << "At timepoint: " << tmp << std::endl;
                        }

                        //This part kills the performance the longer the array gets
                        //Impractical for large data sets
                        //assume generated file has unique timestamps
                        /*
                        if (tmp < 0 || dset->ContainsRecordAtTime(tmp)) {
                            return ParserStatus::ERR_WRONG_FILE_CONTENT;
                        }
                        */
                        //Using hashmap instead
#ifndef __READER_PARSER_ENGINE_53_DISABLE_TIME_UNIQ_TEST__

                        if (tmp < 0 || hashtable.contains(std::uint32_t(tmp))) {
                            return ParserStatus::ERR_WRONG_FILE_CONTENT;
                        }

                        hashtable.insert(std::uint32_t(tmp));
#else
                        if (tmp < 0) {
                            return ParserStatus::ERR_WRONG_FILE_CONTENT;
                        }
#endif
                        record_tmp.t = std::uint32_t(tmp);
                    }
                    break;
                case VAR_INDEXED:
                    if (stage1) {
                        return ParserStatus::ERR_WRONG_FILE_CONTENT;
                    } else {
                        int tmp = std::atoi(match.str(1).c_str());
                        /*
                         * Fail if:
                         *  Index negative
                         *  or Index definition not present
                         *  or Index already exist in temporary record
                         */
                        if (tmp < 0 || !dset->index_map.contains(tmp)
                                || record_tmp.d.contains(tmp)) {
                            return ParserStatus::ERR_WRONG_FILE_CONTENT;
                        }

                        double val_tmp = std::atof(match.str(2).c_str());

                        record_tmp.d[tmp] = val_tmp;
                    }
                    break;
                case COMMENT:
                    break;
                case VERSION:
                    //is also a comment so no harm done when it happens during stage 2 though incorrect
                    break;
                case EMPTY:
                    break;
                case UNKNOWN:
                    return ParserStatus::ERR_WRONG_FILE_CONTENT;
                    break;
            }
        }

        //sanity all elements has idx 1, idx 1 read from filer
        if (!dset->index_map.contains(DatasetV53::PWR_IDX)) {
            return ParserStatus::ERR_WRONG_FILE_CONTENT;
        }

        for (const auto& r : dset->data) {
            if (!r.d.contains(DatasetV53::PWR_IDX)) {
                return ParserStatus::ERR_WRONG_FILE_CONTENT;
            }
        }

        return ParserStatus::SUCCESS;
    }

    ParserEngineV53::SegmentType ParserEngineV53::ParseLine(std::string line, std::smatch &match)
    {
        if (std::regex_match(line, match, REGEX_VERSION)) {
#ifdef __READER_PARSER_ENGINE_V5_3_DEBUG__
            std::clog << "\tfound version: " << match.str(1) << std::endl;
#endif
            return SegmentType::VERSION;

        } else if (std::regex_match(line, match, REGEX_COMMENT)) {
#ifdef __READER_PARSER_ENGINE_V5_3_DEBUG__
            std::clog << "\tfound comment " << std::endl;
#endif
            return SegmentType::COMMENT;
        } else if (std::regex_match(line, match, REGEX_TIME_RESOLUTION)) {
#ifdef __READER_PARSER_ENGINE_V5_3_DEBUG__
            std::clog << "\tfound time_resolution: " << match.str(1) << std::endl;
#endif
            return SegmentType::TIME_RESOLUTION;
        } else if (std::regex_match(line, match, REGEX_HIER_SEPARATOR)) {
#ifdef __READER_PARSER_ENGINE_V5_3_DEBUG__
            std::clog << "\tfound hier_separator: " << match.str(1) << std::endl;
#endif
            return SegmentType::HIER_SEPARATION;
        } else if (std::regex_match(line, match, REGEX_INDEX)) {
#ifdef __READER_PARSER_ENGINE_V5_3_DEBUG__
            std::clog << "\tfound index: " 
                << " Name: " << match.str(1)
                << " Idx ID: " << match.str(2)
                << " Unit: " << match.str(3) << std::endl;
#endif
            return SegmentType::INDEX;
        } else if (std::regex_match(line, match, REGEX_VAR_INDEPENDENT)) {
#ifdef __READER_PARSER_ENGINE_V5_3_DEBUG__
            static bool once = false;
            if(!once) {
                std::clog << "\tfound var independent: " << match.str(1) << std::endl;
                once = true;
            }
#endif
            return SegmentType::VAR_INDEPENDENT;
        } else if (std::regex_match(line, match, REGEX_VAR_INDEXED)) {
#ifdef __READER_PARSER_ENGINE_V5_3_DEBUG__
            static int cnt = 0;
            if(cnt < 5 ) {
                std::clog << "\tfound var indexed: " 
                    << " Idx: " << match.str(1)
                    << " Val: " << match.str(2) << std::endl;
                cnt++;
            }
#endif
            return SegmentType::VAR_INDEXED;
        } else if (line.empty()) {
#ifdef __READER_PARSER_ENGINE_V5_3_DEBUG__
            std::clog << "\tfound empty line\n";
#endif
            return SegmentType::EMPTY;
        } else {
#ifdef __READER_PARSER_ENGINE_V5_3_DEBUG__
            std::clog << "\tunknown line: (" << line << ")\n";
#endif
            return SegmentType::UNKNOWN;
        }
    }

    const std::regex ParserEngineV53::REGEX_VERSION = std::regex(
            ".*![ ]+output_format[ ]+([0-9]+\\.{0,1}[0-9]+)$",
            std::regex::extended);

    const std::regex ParserEngineV53::REGEX_COMMENT = std::regex(
            "^;.*",
            std::regex::extended);

    const std::regex ParserEngineV53::REGEX_TIME_RESOLUTION = std::regex(
            "^\\.time_resolution[ ]+([0-9]+\\.{0,1}[0-9]+)$",
            std::regex::extended);

    const std::regex ParserEngineV53::REGEX_HIER_SEPARATOR = std::regex(
            "^\\.hier_separator[ ]+(.+)",
            std::regex::extended);

    const std::regex ParserEngineV53::REGEX_INDEX = std::regex(
            "^\\.index[ ]+(.+)[ ]+([0-9]+)[ ]+(.+)",
            std::regex::extended);

    const std::regex ParserEngineV53::REGEX_VAR_INDEPENDENT = std::regex(
            "^([0-9]+)",
            std::regex::extended);

    //Might need stronger
    const std::regex ParserEngineV53::REGEX_VAR_INDEXED = std::regex(
            //"^([0-9]+)[ ]+(.+)",
            //Second element captures scientific notation
            "^([0-9]+)[ ]+(-{0,1}[0-9]+\\.{0,1}[0-9]*e{0,1}[-|+]{0,1}[0-9]*)",
            //"^([0-9]+)[ ]+([0-9\\.\\-e]+)",
            std::regex::extended);
}

