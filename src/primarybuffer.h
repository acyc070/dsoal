#ifndef PRIMARYBUFFER_H
#define PRIMARYBUFFER_H

#include <atomic>
#include <dsound.h>


class PrimaryBuffer final : IDirectSoundBuffer {
    std::atomic<ULONG> mRef{0u};

    DWORD mFlags{0u};

public:
    PrimaryBuffer();
    ~PrimaryBuffer();

    /*** IUnknown methods ***/
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) noexcept override;
    ULONG STDMETHODCALLTYPE AddRef() noexcept override;
    ULONG STDMETHODCALLTYPE Release() noexcept override;
    /*** IDirectSoundBuffer methods ***/
    HRESULT STDMETHODCALLTYPE GetCaps(DSBCAPS *bufferCaps) noexcept override;
    HRESULT STDMETHODCALLTYPE GetCurrentPosition(DWORD *playCursor, DWORD *writeCursor) noexcept override;
    HRESULT STDMETHODCALLTYPE GetFormat(WAVEFORMATEX *wfxFormat, DWORD sizeAllocated, DWORD *sizeWritten) noexcept override;
    HRESULT STDMETHODCALLTYPE GetVolume(LONG *volume) noexcept override;
    HRESULT STDMETHODCALLTYPE GetPan(LONG *pan) noexcept override;
    HRESULT STDMETHODCALLTYPE GetFrequency(DWORD *frequency) noexcept override;
    HRESULT STDMETHODCALLTYPE GetStatus(DWORD *status) noexcept override;
    HRESULT STDMETHODCALLTYPE Initialize(IDirectSound *directSound, const DSBUFFERDESC *dsBufferDesc) noexcept override;
    HRESULT STDMETHODCALLTYPE Lock(DWORD offset, DWORD bytes, void **audioPtr1, DWORD *audioBytes1, void **audioPtr2, DWORD *audioBytes2, DWORD flags) noexcept override;
    HRESULT STDMETHODCALLTYPE Play(DWORD reserved1, DWORD reserved2, DWORD flags) noexcept override;
    HRESULT STDMETHODCALLTYPE SetCurrentPosition(DWORD newPosition) noexcept override;
    HRESULT STDMETHODCALLTYPE SetFormat(const WAVEFORMATEX *wfxFormat) noexcept override;
    HRESULT STDMETHODCALLTYPE SetVolume(LONG volume) noexcept override;
    HRESULT STDMETHODCALLTYPE SetPan(LONG pan) noexcept override;
    HRESULT STDMETHODCALLTYPE SetFrequency(DWORD frequency) noexcept override;
    HRESULT STDMETHODCALLTYPE Stop() noexcept override;
    HRESULT STDMETHODCALLTYPE Unlock(void *audioPtr1, DWORD audioBytes1, void *audioPtr2, DWORD audioBytes2) noexcept override;
    HRESULT STDMETHODCALLTYPE Restore() noexcept override;

    template<typename T>
    T as() noexcept { return static_cast<T>(this); }
};

#endif // PRIMARYBUFFER_H
