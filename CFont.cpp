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
