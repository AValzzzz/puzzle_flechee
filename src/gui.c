#include <math.h>
#include "raylib.h"
#include "hexagon.h"
#include "board.h"
#include "input.h"
#include "solver.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 720
#define CELL_SIZE 40
#define BOARD_TOP 120
#define FONT_SIZE 28
#define STEP_DELAY 1.0

#define BACKGROUND (Color){ 40, 40, 40, 255 }
#define COLOR_ONE (Color){ 60, 170, 80, 255 }
#define COLOR_TWO (Color){ 200, 60, 60, 255 }

typedef struct {
    bool board[NB_CELLS];
    int step;
    double timer;
} Animation;

static void startAnimation(Animation *anim, const bool start[])
{
    for (int i = 0; i < NB_CELLS; i++)
        anim->board[i] = start[i];
    anim->step = 0;
    anim->timer = 0;
}

static void updateAnimation(Animation *anim, const Hexagon *hex, const Solution *solution)
{
    if (anim->step == solution->nbClicks)
        return;

    anim->timer += GetFrameTime();
    if (anim->timer < STEP_DELAY)
        return;

    click(hex, anim->board, solution->clicks[anim->step]);
    anim->step++;
    anim->timer = 0;
}

static void drawCenteredText(const char *text, int x, int y, Color color)
{
    int width = MeasureText(text, FONT_SIZE);
    DrawText(text, x - width / 2, y - FONT_SIZE / 2, FONT_SIZE, color);
}

static Vector2 cellCenter(const Hexagon *hex, int cell)
{
    Vector2 center;
    center.x = WINDOW_WIDTH / 2 + hex->q[cell] * CELL_SIZE * 1.5;
    center.y = BOARD_TOP + hex->row[cell] * CELL_SIZE * sqrt(3) / 2;
    return center;
}

static void drawCell(Vector2 center, bool value, bool highlighted)
{
    DrawPoly(center, 6, CELL_SIZE - 3, 0, value ? COLOR_ONE : COLOR_TWO);
    if (highlighted)
        DrawPolyLinesEx(center, 6, CELL_SIZE - 3, 0, 5, GOLD);
    drawCenteredText(value ? "1" : "2", center.x, center.y, WHITE);
}

static void drawBoard(const Hexagon *hex, const bool board[], int highlighted)
{
    for (int i = 0; i < NB_CELLS; i++)
        drawCell(cellCenter(hex, i), board[i], i == highlighted);
}

static void drawStatus(const Animation *anim, const Solution *solution, bool solvable)
{
    const char *text;

    if (!solvable)
        text = "This board has no solution";
    else if (anim->step < solution->nbClicks)
        text = TextFormat("Step %d/%d", anim->step + 1, solution->nbClicks);
    else
        text = TextFormat("Solved in %d clicks!", solution->nbClicks);

    drawCenteredText(text, WINDOW_WIDTH / 2, 40, RAYWHITE);
}

static void drawButton(Rectangle button, const char *text)
{
    bool hovered = CheckCollisionPointRec(GetMousePosition(), button);

    DrawRectangleRec(button, hovered ? SKYBLUE : BLUE);
    drawCenteredText(text, button.x + button.width / 2, button.y + button.height / 2, WHITE);
}

static bool isClicked(Rectangle button)
{
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), button);
}

int main(int argc, char *argv[])
{
    Hexagon hex;
    initHexagon(&hex);

    bool start[NB_CELLS];
    if (!loadBoard(&hex, start, argc, argv))
        return 1;

    Solution solution;
    bool solvable = solve(&hex, start, &solution);
    if (!solvable)
        solution.nbClicks = 0;

    Animation anim;
    startAnimation(&anim, start);

    Rectangle replayButton = { WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT - 90, 160, 50 };

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Puzzle flechee");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (solvable && isClicked(replayButton))
            startAnimation(&anim, start);
        updateAnimation(&anim, &hex, &solution);

        int highlighted = NO_HIGHLIGHT;
        if (anim.step < solution.nbClicks)
            highlighted = solution.clicks[anim.step];

        BeginDrawing();
        ClearBackground(BACKGROUND);
        drawStatus(&anim, &solution, solvable);
        drawBoard(&hex, anim.board, highlighted);
        if (solvable)
            drawButton(replayButton, "Replay");
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
