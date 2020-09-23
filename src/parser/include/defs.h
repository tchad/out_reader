#ifndef __READER_DEFS__
#define __READER_DEFS__


namespace reader {
    enum class DatasetVersion {
        UNDEFINED,
        NULL_SET,
        VER5_3
    };

    enum class ParserStatus {
        SUCCESS,
        ERR_FILE_MISSING,
        ERR_UNSUPPORTED_VERSION,
        ERR_WRONG_FILE_CONTENT,
        ERR_UNKNOWN
    };
}


#endif

