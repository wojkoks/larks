#include "raylib.h"
#include "objects.h"
#include <iostream>
#include <exception>
#include <vector>

//MENU, ALGORYTM_1, ALGORYTM_2, TODO
enum display_content {MENU, ALGORYTM_1, ALGORYTM_2, TODO};

class menu_button {
    
    public:

    Color b_base_color;
    Color b_hover_color;
    Color b_clicked_color;

    Color b_current_color;

    display_content ID;
    Rectangle rect;
    bool mouseOverIt;
    bool isClicked;
    
    menu_button(Rectangle r, Color color, Color hover_color, Color clicked_color, display_content ID) {
        this->b_base_color = color;
        this->b_current_color = color;
        this->b_hover_color = hover_color;
        this->b_clicked_color = clicked_color;
        this->rect = r;
        this->ID = ID;
        std::cout << "Stworzono Przycisk ID: " << this->ID << std::endl;
    }

    ~menu_button(void) {
        std::cout << "Dealokacja przycisku o ID: " << this->ID << std::endl;
    }

    bool isMouseOverThatButton(Vector2 mouse_position) { 
        return CheckCollisionPointRec(mouse_position, this->rect);
    }

    //czy klikamy na przycisk
    bool isButtonClicked() {
        return IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    }

    void setButtonState(display_content &enum_display_value, Vector2 mouse_position) {

        if (isMouseOverThatButton(mouse_position)) {     
            if (isButtonClicked()) {
                this->b_current_color = this->b_clicked_color;
                enum_display_value = this->ID;
            }
            else this->b_current_color = this->b_hover_color;
        }

        else this->b_current_color = this->b_base_color;

        return;
    }
};

void v_draw_buttons(std::vector<menu_button> vector_of_buttons) {

    for (int i = 0; i < vector_of_buttons.size(); i++) {
        
        try {
            DrawRectangleRec(vector_of_buttons[i].rect, vector_of_buttons[i].b_current_color);
            //std::cout << "Drew B:" << vector_of_buttons[i].ID << " with clr.r =" << (int)vector_of_buttons[i].b_current_color.r << std::endl;
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            std::exit(1);
        }
    }
    return;
}

void handle_button_clicks(display_content &enum_display_value, std::vector<menu_button>& vector_of_buttons) {
    
    Vector2 mouse_position = GetMousePosition();

    // Czemu to nie działa??????????????????????????????????????????????
    // for (auto x: vector_of_buttons) {
    //     x.setButtonState(enum_display_value, mouse_position);
    // }

    // A to już tak ????????????????????????????????????????????????????
    for (int i = 0 ; i < vector_of_buttons.size(); i++) {
        vector_of_buttons[i].setButtonState(enum_display_value, mouse_position);
    }

    return;
}

void main_menu(display_content &enum_display_value) {

    //=======
    Color BUTTON_COLOR = RED;
    Color BUTTON_HOVER_COLOR = LIGHTGRAY;
    Color BUTTON_CLICKED_COLOR = WHITE;

    static int MENU_BUTTON_HEIGHT = GetScreenHeight()/16;
    static int MENU_BUTTON_WIDTH = GetScreenWidth()/4;
    static int PADDING_BETWEEN_BUTTONS = MENU_BUTTON_HEIGHT/8;
    static int AMT_OF_BUTTONS = 4;
    static int TOTAL_HEIGHT_OF_BUTTONS_WITH_PADDING = AMT_OF_BUTTONS*MENU_BUTTON_HEIGHT + (AMT_OF_BUTTONS - 1)*PADDING_BETWEEN_BUTTONS; //rozmiar w px bloku przyciskow

    int BUTTON_X = (GetScreenWidth()-MENU_BUTTON_WIDTH)/2; //zeby przyciski byly na srodku ekranu
    
    int BUTTON_Y = (GetScreenHeight()-TOTAL_HEIGHT_OF_BUTTONS_WITH_PADDING)/2; //blok z przyciskami na srodku ekranu

    std::vector<menu_button> vector_of_buttons;

    for (int i = 0; i < AMT_OF_BUTTONS; i++) {
        Rectangle r = {BUTTON_X, BUTTON_Y + i*(MENU_BUTTON_HEIGHT+PADDING_BETWEEN_BUTTONS), MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT};
        menu_button b(r, BUTTON_COLOR, BUTTON_HOVER_COLOR, BUTTON_CLICKED_COLOR, (display_content)i);
        vector_of_buttons.push_back(b);
    }
    
    while(!WindowShouldClose() && enum_display_value == MENU) {

        handle_button_clicks(enum_display_value, vector_of_buttons);

        BeginDrawing();

        ClearBackground(BLACK);
        v_draw_buttons(vector_of_buttons);

        // if (IsKeyDown(KEY_ESCAPE)) break;

        EndDrawing();
    }

    return;
}

void draw(display_content &enum_display_value){

    switch(enum_display_value) {
        case MENU:
            //draw the rest of this stuff
            //przekazujemy to enum_display_value bo w menu możemy wybrać inne opcje, wtedy za pomocą referencji
            //zmienimy wartość tej zmiennej i wyświetlimy co innego
            main_menu(enum_display_value);
            break;
        
        case ALGORYTM_1:
                while(true) {std::cout << "chuj ci w dupe ";}
            break;
        
        case ALGORYTM_2:
            //TODO
            break;
        case TODO:
            //TODO
            break;

        default:
            break;
    }

    return;
};

int main(void) {

    static int WIN_HEIGHT = 1080/2;
    static int WIN_WIDTH = 1920/2;
    
    constexpr int FPS = 60;

    InitWindow(WIN_WIDTH, WIN_HEIGHT, "WINDOW_TITLE");

    display_content Content = MENU;                 //to co chcemy wyświetlić na ekranie, początkowo jest to menu główne

    SetTargetFPS(FPS);

    while(!WindowShouldClose()) {

        // BeginDrawing();

        //     draw(Content);
        //     ClearBackground(BLACK);

        // EndDrawing();
        draw(Content);
    }

    return 0;
}

