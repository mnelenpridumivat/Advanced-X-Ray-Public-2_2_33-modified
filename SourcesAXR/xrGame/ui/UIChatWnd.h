#pragma once
#include "UIDialogWnd.h"
#include "UIWndCallback.h"

class CUIXml;
class CUIGameLog;
class CUIEditBox;
class CUITextWnd;

class CUIChatWnd: public CUIDialogWnd, public CUIWndCallback
{
	typedef CUIDialogWnd inherited;

public:
						CUIChatWnd			();
	void		Show				(bool status) override;
	virtual bool		NeedCursor			() {return false;}
	void				Init				(CUIXml& uiXml);
	void				SetEditBoxPrefix	(LPCSTR prefix);
	void				ChatToAll			(bool b) { sendNextMessageToAll = b; }
	void				PendingMode			(bool const is_pending_mode);
	bool		NeedCursor			()const override {return false;}
	void		SendMessage			(CUIWindow* pWnd, s16 msg, void* pData = nullptr) override;


protected:
	CUIEditBox*			UIEditBox;
	CUITextWnd*			UIPrefix;

	bool				sendNextMessageToAll;
	bool				pendingGameMode;
	
	Frect				pending_prefix_rect;
	Frect				pending_edit_rect;
	
	Frect				inprogress_prefix_rect;
	Frect				inprogress_edit_rect;

	void xr_stdcall		OnChatCommit		(CUIWindow* w, void* d);
	void xr_stdcall		OnChatCancel		(CUIWindow* w, void* d);
};
