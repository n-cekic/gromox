#pragma once
#include <cstdint>
#include <list>
#include <memory>
#include <gromox/mapi_types.hpp>

struct ATTACHMENT_CONTENT;
struct FOLDER_CONTENT;
struct FOLDER_MESSAGES;
struct fxstream_producer;
struct ics_state;
struct logon_object;
struct MESSAGE_CONTENT;
using flow_node = std::pair<uint8_t, const void *>;

struct fxdown_flow_list : public std::list<flow_node> {
	bool record_node(uint8_t, const void * = nullptr);
	bool record_tag(uint32_t);
	bool record_messagelist(EID_ARRAY *);
	bool record_foldermessages(const FOLDER_MESSAGES *);
	bool record_foldermessagesnodelprops(const FOLDER_MESSAGES *);
	bool record_foldercontent(const FOLDER_CONTENT *);
	bool record_foldercontentnodelprops(const FOLDER_CONTENT *);
	bool record_subfoldernodelprops(const FOLDER_CONTENT *);
	bool record_subfolder(const FOLDER_CONTENT *);
};

struct fastdownctx_object final {
	protected:
	fastdownctx_object() = default;
	NOMOVE(fastdownctx_object);

	public:
	~fastdownctx_object();
	static std::unique_ptr<fastdownctx_object> create(logon_object *, uint8_t string_option);
	/* make_xxx function can be invoked only once on the object */
	BOOL make_messagecontent(MESSAGE_CONTENT *);
	BOOL make_attachmentcontent(ATTACHMENT_CONTENT *);
	BOOL make_foldercontent(BOOL subfolders, std::unique_ptr<FOLDER_CONTENT> &&);
	BOOL make_topfolder(std::unique_ptr<FOLDER_CONTENT> &&);
	BOOL make_messagelist(BOOL chginfo, EID_ARRAY *msglst);
	BOOL make_state(ics_state *);
	BOOL get_buffer(void *buf, uint16_t *len, BOOL *last, uint16_t *progress, uint16_t *total);

	std::unique_ptr<fxstream_producer> pstream;
	BOOL b_back = false, b_last = false, b_chginfo = false;
	EID_ARRAY *pmsglst = nullptr;
	std::unique_ptr<FOLDER_CONTENT> pfldctnt;
	fxdown_flow_list flow_list;
	uint32_t total_steps = 0, progress_steps = 0;
};
