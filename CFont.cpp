//GTA SA 1.08
void GetScreenWidthAndHeight(int* w, int* h) {

	// RwEngineGetCurrentVideoMode
	int dwVideoMode = ((int (*)(void))(g_libGTASA + 0x1AE185))();
	RwVideoMode	currentVideoMode;

	// RwEngineGetVideoModeInfo
  	((void (__fastcall *)(RwVideoMode *, int))(g_libGTASA + 0x1AE155))(&currentVideoMode, dwVideoMode);
  	*w = (int)currentVideoMode.width;
  	*h = (int)currentVideoMode.height;

}



void CDebugInfo::Draw()
{
    if (m_uiDrawDebug || m_uiDrawFPS)
    {

        char bufferDebugFps[64];
        char bufferDebugMem[64];

        float* pFPS = (float*)(SA_ADDR(0x608E00));
        sprintf(bufferDebugFps, "FPS: %.1f", *pFPS);
	
        uint32_t msUsed = *(uint32_t*)(g_libGTASA + 0x0067067C);
        uint32_t msAvailable = *(uint32_t*)(g_libGTASA + 0x5DE734);
        sprintf(bufferDebugMem, "MEM: %d/%d", msUsed / (1024 * 1024), msAvailable / (1024 * 1024));

        CFont::SetBackground(false, false);
        CFont::SetProportional(true);
        CFont::SetFontStyle(1);
        CFont::SetScale(1.4f);
        CFont::SetOrientation(1);
        CFont::SetWrapX(640.0f);
	CFont::SetProportional(true);
        CFont::SetEdge(0);
        CFont::SetJustify(false);

        CRGBA bgColor(0, 0, 0, 0);
        CFont::SetBackgroundColor(&bgColor);
        CRGBA textColor(255, 255, 255, 255);
        CFont::SetColor(&textColor);

        int iScreenWidth, iScreenHeight;
        GetScreenWidthAndHeight(&iScreenWidth, &iScreenHeight);

        CFont::PrintString(
            ((float)iScreenWidth / 640.0f) * 4.0f,
            ((float)iScreenHeight / 448.0f) * 200.0f,
            bufferDebugFps);

        CFont::PrintString(
            ((float)iScreenWidth / 640.0f) * 4.0f,
            ((float)iScreenHeight / 448.0f) * 208.0f,
            bufferDebugMem);
    }



#ifdef DEBUG_INFO_ENABLED
    if (!m_uiDrawDebug)

    {
        return;
    }
#endif
}

//GTA SA 2.10 64bit
struct RwVideoMode {
    int width;
    int height;
    int depth;
    int flags;
};

void GetScreenWidthAndHeight(int* w, int* h) {

    // RwEngineGetCurrentVideoMode
    int dwVideoMode = ((int (*)(void))(g_libGTASA + 0x22D0B0))();

    RwVideoMode currentVideoMode;

    // RwEngineGetVideoModeInfo
    ((void (__fastcall *)(RwVideoMode *, int))(g_libGTASA + 0x26EA88))(&currentVideoMode, dwVideoMode);

    *w = currentVideoMode.width;
    *h = currentVideoMode.height;
}

void UI::renderDebug()
{
    if(!pSettings->Get().iFPSCounter) return;

    static float fps = 120.f;
    static auto lastTick = CTimer::m_snTimeInMillisecondsNonClipped;
    if(CTimer::m_snTimeInMillisecondsNonClipped - lastTick > 500) {
        lastTick = CTimer::m_snTimeInMillisecondsNonClipped;
        fps = std::clamp(CTimer::game_FPS, 10.f, 120.f);
    }

    char szStr[64];
    snprintf(szStr, sizeof(szStr), "FPS: %.0f", fps);

    auto &msUsed = CStreaming::ms_memoryUsed;
    auto &msAvailable = CStreaming::ms_memoryAvailable;

    char szStrMem[128];
    snprintf(szStrMem, sizeof(szStrMem), "MEM: %d/%d MB",
             msUsed / (1024 * 1024),
             msAvailable / (1024 * 1024));

    // ตั้งค่าการแสดงผล font
    CFont::SetBackground(false, false);
    CFont::SetProportional(true);
    CFont::SetFontStyle(1);
    CFont::SetScale(1.4f);  // Note : ถ้า Error  เพิ่ม static void SetScale(float w);
    CFont::SetOrientation(1);
    CFont::SetWrapX(640.0f);
    CFont::SetEdge(0);
    CFont::SetJustify(false);

    uint32_t bgColor = 0x00000000;     // โปร่งใส 100%
    uint32_t textColor = 0xFFFFFFFF;   // ขาวเต็ม

    CFont::SetBackgroundColor(&bgColor);
    CFont::SetColor(&textColor);


    int iScreenWidth, iScreenHeight;
    GetScreenWidthAndHeight(&iScreenWidth, &iScreenHeight);

    CFont::PrintString(
        ((float)iScreenWidth / 640.0f) * 4.0f,
        ((float)iScreenHeight / 448.0f) * 200.0f,
        szStr);

    CFont::PrintString(
        ((float)iScreenWidth / 640.0f) * 4.0f,
        ((float)iScreenHeight / 448.0f) * 208.0f,
        szStrMem);
}
