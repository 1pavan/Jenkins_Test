#ifndef __FASTENCODER_H__
#define __FASTENCODER_H__
#include "Transform.h"

struct fast_codec_t;
struct fast_tag_type;

VOLANTE_NAMESPACE_BEGIN

class UniversalOutputRecord;
class UniversalInputRecord;

class VOLANTE_EXPORT FastCodec : public Object {
	fast_codec_t* codec;
public:
	FastCodec();

	virtual ~FastCodec();
	fast_codec_t* getCodec() {
		return codec;
	}
};
class VOLANTE_EXPORT FastEncoder {
public:
	enum {
    NONE = 0,
    COPY = 1,
    INCREMENT = 2,
    DELTA = 3
	};
		int baseTid;
		FastEncoder();
		void initCodec(TransformContext& cxt);
		void onMessageStart(UniversalOutputRecord* record, int tid, TransformContext& cxt);
		void onMessageEnd(UniversalOutputRecord* record, int tid, TransformContext& cxt);

    void writeInt32(UniversalOutputRecord* out, int value, fast_tag_type& tag) ;

    void writeUInt32(UniversalOutputRecord* out, int value, fast_tag_type& tag);

    void writeUInt32(UniversalOutputRecord* out, char value, fast_tag_type& tag);

    void writeUInt32(UniversalOutputRecord* out, const vstring& value, fast_tag_type& tag);

    void writeString(UniversalOutputRecord* out, const vstring& value, fast_tag_type& tag) ;
		FastCodec* fastCodec;
};

class VOLANTE_EXPORT FastDecoder {
public:
	enum {
    NONE = 0,
    COPY = 1,
    INCREMENT = 2,
    DELTA = 3,
	};
		int baseTid;

		FastDecoder();
		void initCodec(TransformContext& cxt);

		void onMessageStart(UniversalInputRecord* record, int tid, TransformContext& cxt);
		void onMessageEnd(UniversalInputRecord* record, int tid, TransformContext& cxt);

    int getInt32(UniversalInputRecord* record, fast_tag_type& tag);


    int getUInt32(UniversalInputRecord* record, fast_tag_type& tag);

    vstring getString(UniversalInputRecord* record, fast_tag_type& tag);

    static vstring toString(int value);

    static vstring toString(long value);

    static char toChar(int value);
		FastCodec* fastCodec;
};

VOLANTE_NAMESPACE_END
#endif //__FASTENCODER_H__
