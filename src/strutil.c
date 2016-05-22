/*
 * string utility file for Internationalized window manager       
 *
 * X11R5 Internationalized Window Manger                     
 * strutil.c ver.1.0  Thu Sep 19 11:11:05 JST 1991
 */
                                                          
/* Copyright 1991 by OMRON Corporation                      
 *
 *      Author: Takashi Inoue    OMRON Corporation
 *                               takashi@ari.ncl.omron.co.jp
 */

#include <stdio.h>
#include <X11/wchar.h>

typedef	unsigned int _State;

wchar_t *convert_mbtowc(mb_str)
char *mb_str;
{
    int mb_len;
    wchar_t *wc_str;
    int wc_len;
    int scanned_bytes;
    
    wc_len = mb_len = strlen(mb_str);
    wc_str = (wchar_t *)malloc(wc_len * sizeof(wchar_t));
    _XConvertMBToWC(NULL, (unsigned char *)mb_str, mb_len,
		    (wchar *)wc_str, &wc_len, &scanned_bytes, (_State *)NULL);
    wc_str[wc_len] = WNULL;
    return (wc_str);
}

char *convert_wctomb(wc_str)
wchar_t *wc_str;
{
    int wc_len;
    char *mb_str;
    int mb_len;
    int scanned_len;
    
    wc_len = wcslen(wc_str);
    mb_len = wc_len * 5 + 1;
    mb_str = (char *)malloc(mb_len * sizeof(char));
    _XConvertWCToMB(NULL, (wchar *)wc_str, wc_len,
		    (unsigned char *)mb_str, &mb_len, &scanned_len);
    mb_str[mb_len] = '\0';
    return (mb_str);
}

char *convert_wctoct(wc_str)
wchar_t *wc_str;
{
    int wc_len;
    char *ct_str;
    int ct_bytes;
    int scanned_len;

    wc_len = wcslen(wc_str);
    ct_bytes = wc_len * 5 + 1;
    ct_str = (char *)malloc(ct_bytes * sizeof(char));
    _XConvertWCToCT(NULL, (wchar *)wc_str, wc_len,
		    (unsigned char *)ct_str, &ct_bytes, &scanned_len);
    ct_str[ct_bytes] = '\0';
    return (ct_str);
}

