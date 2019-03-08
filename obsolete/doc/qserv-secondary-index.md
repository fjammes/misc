# secondary index size for DR1

INT can contain chunkId and subChunkId.

20K chunks * 0.6 * 10E6 objects * (sizeof(BIGINT) + sizeof(INT)) = 144GB
