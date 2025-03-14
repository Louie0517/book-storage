#include "raylib.h"
#include "raygui.h"
#define RAYGUI_IMPLEMENTATION
#include "raymath.h"
#include <math.h>
#include <string.h>
#include "library.c"
#define MAXIMUM_INPUT_CHARS 20

bool loginBox(Rectangle loginRec, const char *loginText, Font forLogin, Color forLoginText, Color *normalColForLogin, Color *hoverColorForLogin, Color *pressedForLogin ,int loginPosX, int loginPos);
bool button(Rectangle rect, const char *text, Color *unPressed, Color Hover, Color PressCol, Font itallic, Color blackBorderr);
void rounder(int roundX, int roundY, int orig_w, int orig_h, int orig_radius, int new_w, int new_h);

void UpdateMainScreen(float *T1, float *T2, float *T3, float screenHeight, float targetY1, float targetY2, float targetY3, Rectangle *ADMIN, Rectangle *STUDENT, Rectangle *CLOSE, bool *adminClick, bool *studentClick, bool *closeClick, int *currentScreen);
void DrawMainScreen(Texture2D logo, int pos2X, int pos2Y, int posX, int posY, Texture2D lib, Rectangle ADMIN, Rectangle STUDENT, Rectangle CLOSE, Color *unPressed, Color hoverColor, Color pressColor, bool *adminClick, bool *studentClick, bool *closeClick, Font itallic, Color MenuBorderButtonCol);

// For Admin
void AdminLoginSpecialButton(const char* ADMtext, int ADMNposX, int ADMNposY, int ADMNwidth, Color ADMNcolor, Font ADMNFont, Rectangle ADMrect, float ADMNthickLine);
void DrawSecondScreen(Font adminIDfont,Texture2D adminDes2, Font adminLetterFont, Texture2D libImageForAdmin, Texture2D imageForAdminLogin, Texture2D admin2, Texture2D books,Texture2D adminLoginBox, Font Shady, float  imageX, float imageY1, float imageY2, float *imageY3, float targetY1, float textX, float *textY, Rectangle adminRec, Color *adminNatButtonCol, Color *adminHovButtonCol, Color adminPresButonCol, Font adminIttalicFont, Color adminBorderColButton, char* adminID, int maximumInputChars, bool *loginSuccessful, Rectangle loginAdminButton, Rectangle backAdminButton, int* currentScreen, const char* correctAdminID, bool* isFocus);
void updateAdminLoginScreen(float *imageX,float *imageY1, float *imageY2 ,float *textX, float widthOfScreen, float heightOfScreen);
void DrawLoginAdminBox( char* adminID, int maximumInputOfChars, float imageY3,  bool isFocus, const char* textPlaceHolder, Font ediFont);
bool DrawAdminButton(int posX, int posY, float width, float height, Font adminLetterFont, const char* adminText, bool hover, Color adminUntouchButton, Color adminHoverColor, Color adminPressedButton, Color adminButtonBorder);
void handleAdminInput(char* userAdminId, int maximumInputChar);

// Admin Menu
void DrawAdminScreen(int *screen, Texture2D browny, Rectangle slideBox, int posXbhie, int posYbhie, Rectangle addRecord, Rectangle editRecord, Rectangle displayAllRec, Rectangle logOut, Font AdminRecFont, Texture2D paris);
void TransitionToPosition(float *posY, float targetY, float speed, Texture2D flower);

// wala lang
void StudentScreen();

int main() {

    InitWindow(1200, 580, "SYSTEM LIBRARY");
    // Main Background
    Texture2D lib = LoadTexture("C://C//Image//yey11.png");
    Texture2D logo = LoadTexture("C://C//Image//logo.png");

    // Admin Login Background
    Texture2D libImageForAdmin = LoadTexture("C://C//Image//yey11.png");
    Texture2D imageForAdminLogin = LoadTexture("C://C//Image//page6.png");
    Texture2D adminBkg2 = LoadTexture("C://C//Image//6.png");
    Texture2D books = LoadTexture("C://C//Image//books.png");
    Texture2D adminLoginBox = LoadTexture("C://C//Image//adminLoginBox.png");
    Texture2D adminDes2 = LoadTexture("C://C//Image//adminDes2.jng");
    Texture2D flowerSparent = LoadTexture("C://C//Image//flowerSparent.jng");
    Texture2D paris = LoadTexture("C://C//Image//tt.png");
    Texture2D browny = LoadTexture("C://C//Image//tt2.png");

    Texture2D modernLib = LoadTexture("C://C//Image//12.png");
    Texture2D p12 = LoadTexture("C://C//Image//p12.png");

    Texture2D editRec = LoadTexture("C://C//Image//13.png");
    Texture2D p13 = LoadTexture("C://C//Image//p13.png");

    Texture2D display = LoadTexture("C://C//Image//18.png");
    Texture2D p14 = LoadTexture("C://C//Image//p14.jng");


    Texture2D deleteRec = LoadTexture("C://C//Image//18.png");
    Texture2D del2 = LoadTexture("C://C//Image//delete.png");


    Texture2D datePick = LoadTexture("C://C//Image//17.png");
    Texture2D calendar = LoadTexture("C://C//Image//calendar.png");
    Texture2D calendartwo = LoadTexture("C://C//Image//calendar.2.png");


    // FONTS
    Font itallic = LoadFont("C://C//Font//Nosifer.ttf");
    Font Shady = LoadFont("C://C//Font//PfD Variable.ttf");
    Font lobster = LoadFont("C://C//Font//Lobsters.ttf");
    Font notoSerif = LoadFont("C://C//Font//NotoSerif-italic.ttf");
    Font pfdItallic = LoadFont("C://C//Font//sigmar.ttf");

    int screenWidth = 1200;
    int screenHeight = 580;
    int posX = 0, pos2X = 310;
    int posY = 0, pos2Y = -logo.height, targetY = 70;

    // Main screen menu
    Rectangle ADMIN = {620, screenHeight + 50, 200, 50};
    Rectangle STUDENT = {620, screenHeight + 50, 200, 50};
    Rectangle CLOSE = {620, screenHeight + 50, 200, 50};

    // Second screen for admin login
    Rectangle adminRec = {320, 229, 229, 40};

    // Button Transition
    float targetY1 = 250;
    float targetY2 = 315;
    float targetY3 = 380;

    // Interpolation factors for Buttons
    float T1 = 0.0f;
    float T2 = 0.0f;
    float T3 = 0.0f;

    // Image transition for Admin login screen
    float imageX = -screenWidth;
    float imageY1 = -screenHeight;
    float imageY2 = screenHeight;
    float textX = screenWidth;

    float imageBoxY = -screenHeight;
    float textBoxY = -screenHeight;


    SetTargetFPS(60);

    // Main menu button colors
    Color MenuoutlineColor = (Color){ 139, 69, 19, 255 };


    Color unPressed = (Color){ 139, 0, 0, 255};
    Color pressColor = (Color){ 139, 0, 0, 192 };
    Color hoverColor = (Color){ 139, 0, 0, 128 };

    hoverColor = pressColor;
    pressColor = unPressed;

    // Second admin login button
    Color naturalColor = (Color){214, 179, 132, 255};
    Color adminLoginHoverColor = (Color){181, 147, 107, 255};
    Color pressedColor = (Color){143, 110, 75, 255};

    adminLoginHoverColor = pressedColor;
    pressedColor = naturalColor;


    // Button color border (Menu)
    Color menuButtonsBorderCol = (Color){139, 69, 19, 255};

    // Main screen menu
    bool adminClick = false;
    bool studentClick = false;
    bool closeClick = false;
    int currentScreen = 0;

    bool addRecClick = false;
    bool EditRecClick = false;
    bool displayRecClick = false;
    bool deleteRecClick = false;
    bool logOutClick = false;

    bool backClick = false;

    // Admin menu Screen (2)
    Rectangle ADDRECORD = {450, 60, 95, 80};
    Rectangle EDITRECORD = {460, 60, 95, 80};
    Rectangle DISPLAYRECORD = {470, 60, 95, 80};
    Rectangle LOGOUT = { 480, 60, 95, 87};

    float posYniKarl = screenHeight;
    float targetSiY = screenHeight - 333;
    float speed = 200.0f;

    // Second screen for admin login
    char userAdminID[MAXIMUM_INPUT_CHARS + 1] = "\0";
    bool adminSuccessfulLogin = false;
    const char* correctUserAdminID = "admin@tup";
    bool isFocus = false;
    bool isAM = true;

    Rectangle slideBox = {screenWidth, 0, 540, 1200};
    float slideSpeed = 600.0f;
    static bool ifBoxOpen = false;

    // LOGIN and BACKBUTTON on admin login screen
    Rectangle adminLoginButton = {610, -screenHeight + 300, 85, 42};
    Rectangle adminBackButton = {475, -screenHeight + 300, 85, 42};


    int selectedDay = 1;
    // january
    int selectedMonth = 0;
    int selectedYear = 2025;
    int selectedHour = 12;
    int selectedMinute = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        // Large loop image square transition
        if (pos2Y < targetY) {
            pos2Y += 14;
            if (pos2Y > targetY) pos2Y = targetY;
        }

        if (IsKeyPressed(KEY_SPACE)) {
                ifBoxOpen = !ifBoxOpen;
                } // Slide in
                if (ifBoxOpen && slideBox.x > screenWidth - slideBox.width) { slideBox.x -= slideSpeed * GetFrameTime();
                } else if (!ifBoxOpen && slideBox.x < screenWidth) {
                    // Slide out
                    slideBox.x += slideSpeed * GetFrameTime();
                }
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentScreen == 0) {
            UpdateMainScreen(&T1, &T2, &T3, screenHeight, targetY1, targetY2, targetY3, &ADMIN, &STUDENT, &CLOSE, &adminClick, &studentClick, &closeClick, &currentScreen);
            DrawMainScreen(logo, posY, pos2Y, posX, posY, lib, ADMIN, STUDENT, CLOSE, &unPressed, hoverColor, pressColor, &adminClick, &studentClick, &closeClick, itallic, RED);
            userAdminID[0] = '\0';
        } else if (currentScreen == 1) {
            updateAdminLoginScreen( &imageX, &imageY1, &imageY2, &textX, screenWidth, screenHeight);
            DrawSecondScreen(notoSerif, adminDes2, lobster, libImageForAdmin, imageForAdminLogin, adminBkg2, books,adminLoginBox , Shady, imageX, imageY1, imageY2, &imageBoxY, targetY1 - 255, textX , &textBoxY, adminRec, &naturalColor, &adminLoginHoverColor, pressedColor, itallic, BROWN, userAdminID, MAXIMUM_INPUT_CHARS, &adminSuccessfulLogin, adminLoginButton, adminBackButton, &currentScreen, correctUserAdminID, &isFocus);
            posY = 0, pos2Y = -logo.height, targetY = 70;
            T1 = T2 = T3 = 0.0f;
if ( IsKeyPressed(KEY_ESCAPE)) {
                currentScreen = 0;
                T1 = T2 = T3 = 0.0f;
                imageX = -screenWidth;
                imageY1 = -screenHeight;
                imageY2 = screenHeight;
                textX = screenWidth;
                imageBoxY = -screenHeight;
                textBoxY = -screenHeight;
                userAdminID[0] = '\0';
                isFocus = false;

                adminLoginButton.y = -screenHeight + 300;
                adminBackButton.y = -screenHeight + 300;
            }
        } else if (currentScreen == 2) {
            posY = 0, pos2Y = -logo.height, targetY = 70;

            if (IsKeyPressed(KEY_BACKSPACE)) {
                currentScreen = 0;
                T1 = T2 = T3 = 0.0f;
            }
        } else if (currentScreen == 3) {
               DrawAdminScreen(&currentScreen, browny, slideBox, screenWidth - 1200, screenHeight - 363,ADDRECORD, EDITRECORD, DISPLAYRECORD, LOGOUT, itallic, paris);
                TransitionToPosition(&posYniKarl, targetSiY, speed, flowerSparent);
                T1 = T2 = T3 = 0.0f;
                posY = 0, pos2Y = -logo.height, targetY = 70;
                userAdminID[0] = '\0';
                isFocus = false;
                imageX = -screenWidth;
                imageY1 = -screenHeight;
                imageY2 = screenHeight;
                textX = screenWidth;
                imageBoxY = -screenHeight;
                textBoxY = -screenHeight;
                adminLoginButton.y = -screenHeight + 300;
                adminBackButton.y = -screenHeight + 300;

        } else if(currentScreen == 4){
            AddRecord(pfdItallic, modernLib, p12, &selectedDay, &selectedMonth, &selectedYear, &selectedHour, &selectedMinute, &currentScreen, &isAM, &screenHeight);
            posYniKarl = screenHeight;

        } else if(currentScreen == 5){

            EditRecord(editRec, p13, pfdItallic, &backClick, &currentScreen);
                        posYniKarl = screenHeight;
        } else if( currentScreen == 6){
            DisplayRecords(&currentScreen, display, p14, &selectedDay, &selectedMonth, &selectedYear, &selectedHour, &selectedMinute, &isAM);
                        posYniKarl = screenHeight;

        } else if(currentScreen == 7){
            SearchRecord(display, &currentScreen, &selectedDay, &selectedMonth, &selectedYear, &selectedHour, &selectedMinute );
                        posYniKarl = screenHeight;

        } else  if(currentScreen == 8){
            DeleteRecord(&currentScreen, deleteRec, del2);
                        posYniKarl = screenHeight;

        } else if(currentScreen == 9){
            DatePicker(screenWidth, screenHeight , calendar, calendartwo, &selectedDay, &selectedMonth, &selectedYear, &selectedHour, &selectedMinute, &isAM,&currentScreen);
        }

        EndDrawing();
    }

    UnloadTexture(lib);
    UnloadTexture(logo);
    UnloadTexture(libImageForAdmin);
    UnloadTexture(imageForAdminLogin);
    UnloadTexture(adminBkg2);
    UnloadFont(itallic);
    UnloadFont(Shady);
    CloseWindow();

    return 0;
}


void rounder(int roundX, int roundY, int orig_w, int orig_h, int orig_radius, int new_w, int new_h){

float scale_w = (float)new_w / orig_w;
float scale_h = (float)new_h / orig_h;

int new_radius = orig_radius * (scale_w < scale_h ? scale_w : scale_h);

Color transparent = (Color){255, 255, 255, 128};

DrawRectangleRounded((Rectangle){roundX, roundY, new_w, new_h}, (float)new_radius / new_w, 16, transparent);

}

void DrawMainScreen(Texture2D logo,int pos2X, int pos2Y, int posX, int posY, Texture2D lib, Rectangle ADMIN, Rectangle STUDENT, Rectangle CLOSE, Color *unPressed, Color hoverColor, Color pressColor, bool *adminClick, bool *studentClick, bool *closeClick, Font itallic, Color MenuBorderButtonCol){
    DrawTexture(lib, posX, posY, WHITE);
    rounder(530, 80, 200, 280, 12, 410, 410);
    DrawTexture(logo, pos2X + 470, pos2Y, WHITE);

    *adminClick = button(ADMIN, "Admin Login", unPressed, hoverColor, pressColor, itallic, MenuBorderButtonCol);
    *studentClick = button(STUDENT, "Student Duo", unPressed, hoverColor, pressColor, itallic ,MenuBorderButtonCol);
    *closeClick = button(CLOSE, "Close", unPressed, hoverColor, pressColor, itallic, MenuBorderButtonCol);
}

void updateAdminLoginScreen(float *imageX,float *imageY1, float *imageY2 ,float *textX, float widthOfScreen, float heightOfScreen){
    // transition
    if(*imageX < 0){
        *imageX += 40;
        if (*imageX > 0 ) *imageX = 0;
    }
    if(*imageY1 < 0) {
        *imageY1 += 15;
        if(*imageY1 > 0) *imageY1 =  0;
    }
    if(*imageY2 > heightOfScreen - 200){
        *imageY2 -=8;
        if(*imageY2 < heightOfScreen - 200) *imageY2 = heightOfScreen - 200;
    }
    if (*textX > 100){
        *textX -= 17;
        if(*textX < 100) *textX = 100;
    }
}

bool button(Rectangle rect, const char *text, Color *unPressed, Color Hover, Color PressCol, Font itallic, Color blackBorder) {
    static bool buttonSelect = false;
    float radius = 10.0f;
    float borderThickness = 2.0f;

    if (CheckCollisionPointRec(GetMousePosition(), rect)) {
        *unPressed = Hover;
        if (IsKeyPressed(KEY_ENTER)) {
            *unPressed = PressCol;
            return true;
        } else if(IsKeyReleased(KEY_ENTER) && buttonSelect){
            *unPressed = Hover;
            buttonSelect = false;
            return true;
            }
        } else {
            *unPressed = (buttonSelect) ?  PressCol : *unPressed;
            buttonSelect = true;
        }
        // Border Formula
    DrawRectangle(rect.x + radius - borderThickness, rect.y - borderThickness, rect.width - 2 * (radius - borderThickness), rect.height + 2 * borderThickness, blackBorder);
    DrawRectangle(rect.x - borderThickness, rect.y + radius - borderThickness, rect.width + 2 * borderThickness, rect.height - 2 * (radius - borderThickness), blackBorder);
    DrawCircle(rect.x + radius, rect.y + radius, radius + borderThickness, blackBorder);
    DrawCircle(rect.x + rect.width - radius, rect.y + radius, radius + borderThickness, blackBorder);
    DrawCircle(rect.x + radius, rect.y + rect.height - radius, radius + borderThickness, blackBorder);
    DrawCircle(rect.x + rect.width - radius, rect.y + rect.height - radius, radius + borderThickness, blackBorder);

        // Rounded Formula
    DrawRectangle(rect.x + radius, rect.y, rect.width - 2 * radius, rect.height, *unPressed);
    DrawRectangle(rect.x, rect.y + radius, rect.width, rect.height - 2 * radius, *unPressed);
    DrawCircle(rect.x + radius, rect.y + radius, radius, *unPressed);
    DrawCircle(rect.x + rect.width - radius, rect.y + radius, radius, *unPressed);
    DrawCircle(rect.x + radius, rect.y + rect.height - radius, radius, *unPressed);
    DrawCircle(rect.x + rect.width - radius, rect.y + rect.height - radius, radius, *unPressed);

    Color colorOfText = (Color){ 244, 164, 96, 255 };
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 20, 1);
    // Center text horizontally
    float textPos = rect.x + (rect.width - textSize.x) / 2.0f;
    DrawTextEx(itallic, text, (Vector2){textPos - 10, rect.y + ((rect.height - textSize.y) / 3)}, 24, 1, GOLD);

    return false;
}

void UpdateMainScreen(float *T1, float *T2, float *T3, float screenHeight, float targetY1, float targetY2, float targetY3, Rectangle *ADMIN, Rectangle *STUDENT, Rectangle *CLOSE, bool *adminClick, bool *studentClick, bool *closeClick, int *currentScreen) {
    // transition for glass box xdx
    if (*T1 < 1.0f) *T1 += 0.05f;
    if (*T2 < 1.0f && *T1 >= 1.0f) *T2 += 0.05f;
    if (*T3 < 1.0f && *T2 >= 1.0f) *T3 += 0.05f;

    ADMIN->y = screenHeight + 50 + (targetY1 - (screenHeight + 50)) * *T1;
    STUDENT->y = screenHeight + 50 + (targetY2 - (screenHeight + 50)) * *T2;
    CLOSE->y = screenHeight + 50 + (targetY3 - (screenHeight + 50)) * *T3;

    if (*adminClick) {
        *currentScreen = 1;
    } else if (*studentClick) {
        *currentScreen = 2;
    } else if (*closeClick) {
        CloseWindow();
    }
}
// screen uno
void DrawSecondScreen(Font adminIDfont, Texture2D adminDes2, Font adminLoginFont, Texture2D libImageForAdmin, Texture2D imageForAdminLogin, Texture2D admin2, Texture2D books, Texture2D adminLoginBox, Font Shady, float imageX, float imageY1, float imageY2, float *imageY3 ,float targetY1 ,float textX, float *textY, Rectangle adminRec, Color *adminNatButtonCol, Color *adminHovButtonCol, Color adminPresButonCol, Font adminIttalicFont, Color adminBorderColButton, char* adminID, int maximumInputChars, bool *loginSuccessful, Rectangle loginAdminButton, Rectangle backAdminButton, int* currentScreen, const char* correctAdminID, bool* isFocus) {

    ClearBackground(RAYWHITE);

    if(*imageY3 < targetY1 ){
        *imageY3 += 10;
        *textY += 10;
    }
    else {
        *imageY3 = targetY1;
        *textY = targetY1;
    }

    DrawTexture(libImageForAdmin, 0, 0, WHITE);
    DrawTexture(imageForAdminLogin, (int)imageX -1, -1, WHITE);
    DrawTexture(admin2, 820, (int)imageY1, WHITE);
    DrawTexture(books, 885, (int)imageY2 , WHITE);
    DrawTexture(adminDes2, 0, (int)imageY2 - 292, WHITE);

    DrawTextEx(Shady, "Reading\nis\ndreaming\nwith\nopen eyes.", (Vector2){textX + 795, 100}, 65, 0, ORANGE);
    // whr login buttns plce
    DrawLoginAdminBox(adminID, maximumInputChars, *imageY3, *isFocus, "Admin Id:", adminLoginFont);

    // button position with the img
    loginAdminButton.y = *imageY3 + 300;
    backAdminButton.y = *imageY3 + 300;

    Color normalState = (Color){139, 0, 0, 255};
    Color hoverState = (Color){139, 0, 0, 128};

    bool loginButtonHover = CheckCollisionPointRec(GetMousePosition(), (Rectangle){465, 320, 150, 200});
    DrawAdminButton(465, *imageY3 + 320, 150, 60, adminLoginFont, "Login", loginButtonHover, *adminNatButtonCol, normalState, hoverState, BLACK);

    bool backButtonHover = CheckCollisionPointRec(GetMousePosition(), (Rectangle){60, 80, 70, 90});
    DrawAdminButton(215, *imageY3 + 320, 150, 60, adminLoginFont, "Back", backButtonHover, GOLD, normalState, hoverState, BLACK);


    if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){215, *imageY3 + 230, 395, 60}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
       *isFocus = true;
       } else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        *isFocus = false;
    }
       if(*isFocus){
                handleAdminInput(adminID, maximumInputChars);
       }
        // password part
    if(loginButtonHover && IsKeyPressed(KEY_ENTER)){
        // scanning ID
        if(strcmp(adminID, correctAdminID) == 0){
            *loginSuccessful = true;
           *currentScreen = 3;
        }
    }
    bool tride = false;
    Vector2 che = GetMousePosition();
    Rectangle he = {215, *imageY3 + 320, 150, 60};
    if(CheckCollisionPointRec(che, he)){
        tride = true;
    }
    if(tride && IsKeyPressed(KEY_ENTER)){
            *currentScreen = 0;
            *loginSuccessful = false;
             adminID[0] = '\0';
        }
    }

void DrawLoginAdminBox( char* adminID, int maximumInputOfChars, float imageY3, bool isFocus, const char* textPlaceHolder, Font ediFont){

    Color transparentWhite = (Color){255, 255, 255, 128};
    rounder(165, imageY3 + 90, 580, 450, 20, 500, 375);
    DrawTextEx(ediFont, "Login", (Vector2){300, imageY3 + 120}, 90, 2.0f, ORANGE);
    DrawRectangle(215, imageY3 + 230, 395, 60, isFocus ? transparentWhite : WHITE);
    DrawRectangleLines(215, imageY3 + 230, 395, 60, BLACK);

        if(strlen(adminID) == 0 && !isFocus){
                 DrawTextEx(ediFont, textPlaceHolder, (Vector2){218, imageY3 + 233}, 30, 0 ,BLACK);
        } else{
            DrawTextEx(ediFont, adminID, (Vector2){218, imageY3 + 233}, 20, 0, BLACK);
    }

}

bool DrawAdminButton(int posX, int posY, float width, float height, Font adminLetterFont, const char* adminText, bool hover, Color adminUntouchButton, Color adminHoverColor, Color adminPressedButton, Color adminButtonBorder) {
    static bool adminButton = false;
    float radius = 2.0f;
    float borderThickness = 2.0f;


    Rectangle adminLoginButton = { posX, posY, width, height };

    if (CheckCollisionPointRec(GetMousePosition(), adminLoginButton)) {
        adminUntouchButton = adminHoverColor;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            adminUntouchButton = adminPressedButton;
            return true;
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && adminButton) {
            adminUntouchButton = adminHoverColor;
            adminButton = false;
            return true;
        }
    } else {
        adminUntouchButton = (adminButton) ? adminPressedButton : adminUntouchButton;
        adminButton = true;
    }


    DrawRectangle(adminLoginButton.x + radius - borderThickness, adminLoginButton.y - borderThickness, adminLoginButton.width - 2 * (radius - borderThickness), adminLoginButton.height + 2 * borderThickness, adminButtonBorder);
    DrawRectangle(adminLoginButton.x - borderThickness, adminLoginButton.y + radius - borderThickness, adminLoginButton.width + 2 * borderThickness, adminLoginButton.height - 2 * (radius - borderThickness), adminButtonBorder);
    DrawCircle(adminLoginButton.x + radius, adminLoginButton.y + radius, radius + borderThickness, adminButtonBorder);
    DrawCircle(adminLoginButton.x + adminLoginButton.width - radius, adminLoginButton.y + radius, radius + borderThickness, adminButtonBorder);
    DrawCircle(adminLoginButton.x + radius, adminLoginButton.y + adminLoginButton.height - radius, radius + borderThickness, adminButtonBorder);
    DrawCircle(adminLoginButton.x + adminLoginButton.width - radius, adminLoginButton.y + adminLoginButton.height - radius, radius + borderThickness, adminButtonBorder);

    DrawRectangle(adminLoginButton.x + radius, adminLoginButton.y, adminLoginButton.width - 2 * radius, adminLoginButton.height, adminUntouchButton);
    DrawRectangle(adminLoginButton.x, adminLoginButton.y + radius, adminLoginButton.width, adminLoginButton.height - 2 * radius, adminUntouchButton);
    DrawCircle(adminLoginButton.x + radius, adminLoginButton.y + radius, radius, adminUntouchButton);
    DrawCircle(adminLoginButton.x + adminLoginButton.width - radius, adminLoginButton.y + radius, radius, adminUntouchButton);
    DrawCircle(adminLoginButton.x + radius, adminLoginButton.y + adminLoginButton.height - radius, radius, adminUntouchButton);
    DrawCircle(adminLoginButton.x + adminLoginButton.width - radius, adminLoginButton.y + adminLoginButton.height - radius, radius, adminUntouchButton);

    Color adminButtonColor = hover ? adminHoverColor : adminUntouchButton;
    DrawTextEx(adminLetterFont, adminText, (Vector2){adminLoginButton.x + 30, adminLoginButton.y + 10}, 30, 0, GOLD);

    return false;
}

void handleAdminInput(char* userAdminId, int maximumInputChar){
    int key = GetCharPressed();

    while(key > 0){
        if((key >= 32 ) && (key <= 125) && (strlen(userAdminId) < maximumInputChar)){
            userAdminId[strlen(userAdminId)] = (char)key;
            userAdminId[strlen(userAdminId) + 1] = '\0';
        }
        key = GetCharPressed();
    }
    if(IsKeyPressed(KEY_BACKSPACE)){
        int len = strlen(userAdminId);
            if(len > 0){
                userAdminId[len - 1] = '\0';
        }
    }
}
void DrawAdminScreen( int *screen, Texture2D browny, Rectangle slideBox, int posXbhie, int posYbhie, Rectangle addRecord, Rectangle editRecord, Rectangle displayAllRec, Rectangle logOut, Font AdminRecFont, Texture2D paris) {
    static bool ifBoxOpen = false;
    Vector2 buttonSize = {405, 260};
    float slideSpeed = 100.0f;
    static float scrollOffset = 0.0f;
    const int totalButtons = 6;
    const float buttonSpacing = 20.0f;
    const float scrollSpeed = 300.0f;
    float maxScroll = 1360;

    DrawTexture(paris, posXbhie, posYbhie - 217, WHITE);

    if (IsKeyPressed(KEY_SPACE)) {
        ifBoxOpen = !ifBoxOpen;
    }
        // left
    if (ifBoxOpen && slideBox.x > 1200 - slideBox.width) {
        slideBox.x -= slideSpeed * GetFrameTime();
        // right
    } else if (!ifBoxOpen && slideBox.x < 1200) {
        slideBox.x += slideSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_DOWN)) {
        scrollOffset += scrollSpeed * GetFrameTime();
        if (scrollOffset > maxScroll) scrollOffset = maxScroll;
    }
    if (IsKeyDown(KEY_UP)) {
        scrollOffset -= scrollSpeed * GetFrameTime();

        // scroll upwards pataas
        if (scrollOffset < -maxScroll) scrollOffset = -maxScroll;
    }

    DrawTextureRec(browny, (Rectangle){0, 3, browny.width + 30, browny.height}, (Vector2){slideBox.x - 60, slideBox.y }, WHITE);

    Color glass = (Color){ 255, 255, 255, 50 };

    Vector2 mousePos = GetMousePosition();
    // logc for buttns
    if (slideBox.x <= 1200) {
        for (int i = 0; i < totalButtons; i++) {

            Vector2 buttonPos = {
                slideBox.x + 60,
                slideBox.y + 100 + (i * (buttonSize.y + buttonSpacing)) - scrollOffset
            };

            if (buttonPos.y + buttonSize.y > slideBox.y && buttonPos.y < slideBox.y + slideBox.height) {

                Color buttonColor = (i == 0) ? (Color){80, 0, 120, 255} :
                    (i == 1) ? (Color){130, 0, 150, 255} :
                    (i == 2) ? (Color){170, 70, 200, 255} :
                    (i == 3) ? (Color){200, 150, 250, 255} :
                    (i == 4) ? (Color){150, 200, 255, 255} :
                    (Color){50, 0, 80, 255};

                Rectangle buttonRect = {buttonPos.x, buttonPos.y, buttonSize.x, buttonSize.y};
                if (CheckCollisionPointRec(mousePos, buttonRect)) {
                    buttonColor = Fade(buttonColor, 0.7f);
                }
                DrawRectangleV(buttonPos, buttonSize, buttonColor);
                // Border
                DrawRectangleLines(buttonRect.x, buttonRect.y, buttonRect.width, buttonRect.height, PINK);

                Color TEXT_WHITE = (Color){255, 255, 255, 255};
                Color TEXT_LAVENDER = (Color){230, 200, 255, 255};
                Color TEXT_YELLOW = (Color){255, 235, 200, 255};
                Color TEXT_CYAN = (Color){200, 255, 255, 255};

                Color textColor = (i == 0) ? TEXT_WHITE :
                                  (i == 1) ? TEXT_LAVENDER :
                                  (i == 2) ? TEXT_YELLOW :
                                  (i == 3) ? TEXT_CYAN :
                                  TEXT_WHITE;

                const char *buttonText = (i == 0) ? "Add \nRecord" : (i == 1) ? "Edit \nRecords" :
                                         (i == 2) ? "Display \nRecords" :
                                         (i == 3) ? "Search \nRecords" :
                                         (i == 4) ? "Delete \nRecords" : "Logout";
                DrawText(buttonText, buttonPos.x + 78, buttonPos.y + 60, 73, textColor);

                if(IsKeyPressed(KEY_ENTER) && CheckCollisionPointRec(mousePos, buttonRect)){
                    if(i == 0){
                        *screen = 4;
                    }
                    else if(i == 1){
                        *screen = 5;
                    }
                    else if(i == 2){
                        *screen = 6;
                    }
                    else if(i == 3){
                        *screen = 7;
                    }
                    else if(i == 4){
                        *screen = 8;
                    } else if(i == 5){
                        *screen = 0;
                    }
                }
            }
        }
    }
}

void TransitionToPosition(float *posY, float targetY, float speed, Texture2D flower) {
    int heightXbeh = 1200;
    DrawTexture(flower, heightXbeh - 1200, *posY, WHITE);

    if (*posY > targetY) {
        *posY -= speed * GetFrameTime();
        if (*posY < targetY) *posY = targetY;
    }
}
void StudentScreen() {
    DrawText("Third Screen", 40, 60, 100, BLACK);
}
