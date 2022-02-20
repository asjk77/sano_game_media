
/**
 * @brief 문자열 텍스처를 기본 폰트로부터 생성합니다.
 *
 * @param inString 생성할 스트링 텍스처
 * @param outStringTextureRect 생성된 텍스처 Rect (0,0, width, height)
 * @param outStringTextureRect
 *
 * @return 성공시 True
 */
TexturePtr CreateStringTextureFromBaseFont(const char* inString,
                                           Color& inColor);

/**
 * @brief 현제 화면에 좌표를 기준으로 문자열을 그립니다.
 *
 * @param inPosX X좌표
 * @param inPosY Y좌표
 * @param inString 문자열
 */
void DrawString(int inPosX, int inPosY, const char* inString);

/**
 * @brief 현제 화면 좌표를 기준으로 문자열을 그립니다.
 *
 * @param inPosX X좌표
 * @param inPosY Y좌표
 * @param inString 스트링
 * @param inFont 폰트 객체
 * @param inColor 컬러
 */
void DrawString(int inPosX, int inPosY, const char* inString,
                const FontPtr& inFont, Color& inColor);

/**
 * @brief 현제 화면 좌표를 기준으로 폰트 키를 이용하여 문자열을 그립니다.
 *
 * @param inPosX 그릴 좌표 X
 * @param inPosY 그릴 좌표 Y
 * @param inString 그릴 좌표 String
 * @param inFontKey FontManager에 등록된 키
 * @param inColor 컬러
 */
void DrawString(int inPosX, int inPosY, const char* inString,
                const FontKey& inKey, Color& inColor);

