/*
 * 
Copyright 1989, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.
 * */

/***********************************************************************
 *
 * $Xorg: iconmgr.h,v 1.4 2001/02/09 02:05:36 xorgcvs Exp $
 *
 * Icon Manager includes
 *
 * 09-Mar-89 Tom LaStrange		File Created
 *
 ***********************************************************************/

#ifndef _ICONMGR_
#define _ICONMGR_

typedef struct WList
{
    struct WList *next;
    struct WList *prev;
    struct TwmWindow *twm;
    struct IconMgr *iconmgr;
    Window w;
    Window icon;
    int x, y, width, height;
    int row, col;
    int me;
    Pixel fore, back, highlight;
    unsigned top, bottom;
    short active;
    short down;
} WList;

typedef struct IconMgr
{
    struct IconMgr *next;		/* pointer to the next icon manager */
    struct IconMgr *prev;		/* pointer to the previous icon mgr */
    struct IconMgr *lasti;		/* pointer to the last icon mgr */
    struct WList *first;		/* first window in the list */
    struct WList *last;			/* last window in the list */
    struct WList *active;		/* the active entry */
    TwmWindow *twm_win;			/* back pointer to the new parent */
    struct ScreenInfo *scr;		/* the screen this thing is on */
    Window w;				/* this icon manager window */
    char *geometry;			/* geometry string */
    char *name;
    char *icon_name;
    int x, y, width, height;
    int columns, cur_rows, cur_columns;
    int count;
} IconMgr;

extern int iconmgr_textx;
extern WList *DownIconManager;

extern void CreateIconManagers();
extern IconMgr *AllocateIconManager();
extern void MoveIconManager();
extern void JumpIconManager();
extern WList *AddIconManager();
extern void InsertInIconManager();
extern void RemoveFromIconManager();
extern void RemoveIconManager();
extern void ActiveIconManager();
extern void NotActiveIconManager();
extern void DrawIconManagerBorder();
extern void SortIconManager();
extern void PackIconManager();


#endif /* _ICONMGR_ */
