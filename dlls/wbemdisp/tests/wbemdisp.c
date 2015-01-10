/*
 * Copyright 2015 Hans Leidekker for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#define COBJMACROS

#include <stdio.h>
#include "windows.h"
#include "initguid.h"
#include "objidl.h"
#include "wbemdisp.h"
#include "wine/test.h"

DEFINE_GUID(CLSID_WINMGMTS,0x172bddf8,0xceea,0x11d1,0x8b,0x05,0x00,0x60,0x08,0x06,0xd9,0xb6);

static void test_ParseDisplayName(void)
{
    static const WCHAR name1[] =
        {'w','i','n','m','g','m','t','s',':',0};
    static const WCHAR name2[] =
        {'w','i','n','m','g','m','t','s',':','\\','\\','.','\\','r','o','o','t','\\','c','i','m','v','2',0};
    static const WCHAR name3[] =
        {'w','i','n','m','g','m','t','s',':','\\','\\','.','\\','r','o','o','t','\\','c','i','m','v','2',':',
         'W','i','n','3','2','_','L','o','g','i','c','a','l','D','i','s','k','.',
         'D','e','v','i','c','e','I','D','=','\'','C',':','\'',0};
    static const WCHAR name4[] =
        {'w','i','n','m','g','m','t','s',':','\\','\\','.','\\','r','o','o','t','\\','c','i','m','v','2',':',
         'W','i','n','3','2','_','S','e','r','v','i','c','e',0};
    static const struct
    {
        const WCHAR *name;
        HRESULT      hr;
        REFIID       iid;
        ULONG        eaten;
    } tests[] =
    {
        { name1, S_OK, &IID_ISWbemServices, sizeof(name1)/sizeof(name1[0]) - 1 },
        { name2, S_OK, &IID_ISWbemServices, sizeof(name2)/sizeof(name2[0]) - 1 },
        { name3, S_OK, &IID_ISWbemObject, sizeof(name3)/sizeof(name3[0]) - 1 },
        { name4, S_OK, &IID_ISWbemObject, sizeof(name4)/sizeof(name4[0]) - 1 }
    };
    IParseDisplayName *displayname;
    IBindCtx *ctx;
    IMoniker *moniker;
    IUnknown *obj;
    BSTR str;
    ULONG i, eaten;
    HRESULT hr;

    hr = CoCreateInstance( &CLSID_WINMGMTS, NULL, CLSCTX_INPROC_SERVER, &IID_IParseDisplayName, (void **)&displayname );
    if (hr != S_OK)
    {
        win_skip( "can't create instance of WINMGMTS\n" );
        return;
    }

    hr = CreateBindCtx( 0, &ctx );
    ok( hr == S_OK, "got %x\n", hr );

    for (i =0; i < sizeof(tests)/sizeof(tests[0]); i++)
    {
        str = SysAllocString( tests[i].name );
        eaten = 0xdeadbeef;
        moniker = NULL;
        hr = IParseDisplayName_ParseDisplayName( displayname, NULL, str, &eaten, &moniker );
        SysFreeString( str );
        ok( hr == tests[i].hr, "%u: got %x\n", i, hr );
        ok( eaten == tests[i].eaten, "%u: got %u\n", i, eaten );
        if (moniker)
        {
            obj = NULL;
            hr = IMoniker_BindToObject( moniker, ctx, NULL, tests[i].iid, (void **)&obj );
            ok( hr == S_OK, "%u: got %x\n", i, hr );
            if (obj) IUnknown_Release( obj );
            IMoniker_Release( moniker );
        }
    }

    IBindCtx_Release( ctx );
    IParseDisplayName_Release( displayname );
}

START_TEST(wbemdisp)
{
    CoInitialize( NULL );
    test_ParseDisplayName();
    CoUninitialize();
}
