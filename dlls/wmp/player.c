/*
 * Copyright 2014 Jacek Caban for CodeWeavers
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

#include "wmp_private.h"

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(wmp);

static inline WindowsMediaPlayer *impl_from_IWMPPlayer4(IWMPPlayer4 *iface)
{
    return CONTAINING_RECORD(iface, WindowsMediaPlayer, IWMPPlayer4_iface);
}

static HRESULT WINAPI WMPPlayer4_QueryInterface(IWMPPlayer4 *iface, REFIID riid, void **ppv)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    return IOleObject_QueryInterface(&This->IOleObject_iface, riid, ppv);
}

static ULONG WINAPI WMPPlayer4_AddRef(IWMPPlayer4 *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    return IOleObject_AddRef(&This->IOleObject_iface);
}

static ULONG WINAPI WMPPlayer4_Release(IWMPPlayer4 *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    return IOleObject_Release(&This->IOleObject_iface);
}

static HRESULT WINAPI WMPPlayer4_GetTypeInfoCount(IWMPPlayer4 *iface, UINT *pctinfo)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pctinfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_GetTypeInfo(IWMPPlayer4 *iface, UINT iTInfo,
        LCID lcid, ITypeInfo **ppTInfo)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%u %d %p)\n", This, iTInfo, lcid, ppTInfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_GetIDsOfNames(IWMPPlayer4 *iface, REFIID riid,
        LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%s %p %u %d %p)\n", This, debugstr_guid(riid), rgszNames, cNames, lcid, rgDispId);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_Invoke(IWMPPlayer4 *iface, DISPID dispIdMember,
        REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult,
        EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%d %s %d %x %p %p %p %p)\n", This, dispIdMember, debugstr_guid(riid), lcid,
          wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_close(IWMPPlayer4 *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_URL(IWMPPlayer4 *iface, BSTR *pbstrURL)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pbstrURL);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_URL(IWMPPlayer4 *iface, BSTR url)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(url));
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_openState(IWMPPlayer4 *iface, WMPOpenState *pwmpos)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pwmpos);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_playState(IWMPPlayer4 *iface, WMPPlayState *pwmpps)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pwmpps);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_controls(IWMPPlayer4 *iface, IWMPControls **ppControl)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppControl);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_settings(IWMPPlayer4 *iface, IWMPSettings **ppSettings)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppSettings);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_currentMedia(IWMPPlayer4 *iface, IWMPMedia **ppMedia)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppMedia);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_currentMedia(IWMPPlayer4 *iface, IWMPMedia *pMedia)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pMedia);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_mediaCollection(IWMPPlayer4 *iface, IWMPMediaCollection **ppMediaCollection)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppMediaCollection);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_playlistCollection(IWMPPlayer4 *iface, IWMPPlaylistCollection **ppPlaylistCollection)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppPlaylistCollection);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_versionInfo(IWMPPlayer4 *iface, BSTR *pbstrVersionInfo)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pbstrVersionInfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_launchURL(IWMPPlayer4 *iface, BSTR url)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(url));
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_network(IWMPPlayer4 *iface, IWMPNetwork **ppQNI)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppQNI);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_currentPlaylist(IWMPPlayer4 *iface, IWMPPlaylist **ppPL)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppPL);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_currentPlaylist(IWMPPlayer4 *iface, IWMPPlaylist *pPL)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pPL);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_cdromCollection(IWMPPlayer4 *iface, IWMPCdromCollection **ppCdromCollection)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppCdromCollection);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_closedCaption(IWMPPlayer4 *iface, IWMPClosedCaption **ppClosedCaption)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppClosedCaption);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_isOnline(IWMPPlayer4 *iface, VARIANT_BOOL *pfOnline)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pfOnline);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_Error(IWMPPlayer4 *iface, IWMPError **ppError)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppError);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_Status(IWMPPlayer4 *iface, BSTR *pbstrStatus)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pbstrStatus);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_dvd(IWMPPlayer4 *iface, IWMPDVD **ppDVD)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppDVD);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_newPlaylist(IWMPPlayer4 *iface, BSTR name, BSTR url, IWMPPlaylist **ppPlaylist)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%s %s %p)\n", This, debugstr_w(name), debugstr_w(url), ppPlaylist);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_newMedia(IWMPPlayer4 *iface, BSTR url, IWMPMedia **ppMedia)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppMedia);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_enabled(IWMPPlayer4 *iface, VARIANT_BOOL *pbEnabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pbEnabled);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_enabled(IWMPPlayer4 *iface, VARIANT_BOOL enabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%x)\n", This, enabled);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_fullScreen(IWMPPlayer4 *iface, VARIANT_BOOL *pbFullScreen)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pbFullScreen);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_fullScreen(IWMPPlayer4 *iface, VARIANT_BOOL fullscreen)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%x)\n", This, fullscreen);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_enableContextMenu(IWMPPlayer4 *iface, VARIANT_BOOL *pbEnableContextMenu)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pbEnableContextMenu);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_enableContextMenu(IWMPPlayer4 *iface, VARIANT_BOOL enable)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%x)\n", This, enable);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_uiMode(IWMPPlayer4 *iface, BSTR mode)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(mode));
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_uiMode(IWMPPlayer4 *iface, BSTR *pbstrMode)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pbstrMode);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_stretchToFit(IWMPPlayer4 *iface, VARIANT_BOOL *enabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, enabled);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_stretchToFit(IWMPPlayer4 *iface, VARIANT_BOOL enabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%x)\n", This, enabled);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_windowlessVideo(IWMPPlayer4 *iface, VARIANT_BOOL *enabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, enabled);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_windowlessVideo(IWMPPlayer4 *iface, VARIANT_BOOL enabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%x)\n", This, enabled);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_isRemote(IWMPPlayer4 *iface, VARIANT_BOOL *pvarfIsRemote)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pvarfIsRemote);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_playerApplication(IWMPPlayer4 *iface, IWMPPlayerApplication **ppIWMPPlayerApplication)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppIWMPPlayerApplication);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_openPlayer(IWMPPlayer4 *iface, BSTR url)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(url));
    return E_NOTIMPL;
}

static IWMPPlayer4Vtbl WMPPlayer4Vtbl = {
    WMPPlayer4_QueryInterface,
    WMPPlayer4_AddRef,
    WMPPlayer4_Release,
    WMPPlayer4_GetTypeInfoCount,
    WMPPlayer4_GetTypeInfo,
    WMPPlayer4_GetIDsOfNames,
    WMPPlayer4_Invoke,
    WMPPlayer4_close,
    WMPPlayer4_get_URL,
    WMPPlayer4_put_URL,
    WMPPlayer4_get_openState,
    WMPPlayer4_get_playState,
    WMPPlayer4_get_controls,
    WMPPlayer4_get_settings,
    WMPPlayer4_get_currentMedia,
    WMPPlayer4_put_currentMedia,
    WMPPlayer4_get_mediaCollection,
    WMPPlayer4_get_playlistCollection,
    WMPPlayer4_get_versionInfo,
    WMPPlayer4_launchURL,
    WMPPlayer4_get_network,
    WMPPlayer4_get_currentPlaylist,
    WMPPlayer4_put_currentPlaylist,
    WMPPlayer4_get_cdromCollection,
    WMPPlayer4_get_closedCaption,
    WMPPlayer4_get_isOnline,
    WMPPlayer4_get_Error,
    WMPPlayer4_get_Status,
    WMPPlayer4_get_dvd,
    WMPPlayer4_newPlaylist,
    WMPPlayer4_newMedia,
    WMPPlayer4_get_enabled,
    WMPPlayer4_put_enabled,
    WMPPlayer4_get_fullScreen,
    WMPPlayer4_put_fullScreen,
    WMPPlayer4_get_enableContextMenu,
    WMPPlayer4_put_enableContextMenu,
    WMPPlayer4_put_uiMode,
    WMPPlayer4_get_uiMode,
    WMPPlayer4_get_stretchToFit,
    WMPPlayer4_put_stretchToFit,
    WMPPlayer4_get_windowlessVideo,
    WMPPlayer4_put_windowlessVideo,
    WMPPlayer4_get_isRemote,
    WMPPlayer4_get_playerApplication,
    WMPPlayer4_openPlayer
};

void init_player_ifaces(WindowsMediaPlayer *wmp)
{
    wmp->IWMPPlayer4_iface.lpVtbl = &WMPPlayer4Vtbl;
}
