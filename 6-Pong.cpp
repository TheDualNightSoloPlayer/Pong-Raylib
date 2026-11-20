#include "raylib.h"

int main() {
	InitWindow(800, 600, "Pong");
	SetTargetFPS(60);

	Rectangle leftPaddle = { 30, 250, 15, 100 };
	Rectangle rightPaddle = { 755, 250 , 15 , 100 };

	Vector2 ballPOS = { 400, 300 };
	Vector2 ballSpeed = { 350.0f, 250.0f };
	float ballRadius = 10.0f;
	float paddleSpeed = 400.0f;
	int leftScore = 0;
	int rightScore = 0;
	bool pauseGame = false;

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		if (IsKeyPressed(KEY_P)) pauseGame = !pauseGame;

		if (!pauseGame) {
			if (IsKeyDown(KEY_W)) leftPaddle.y -= paddleSpeed * dt;
			if (IsKeyDown(KEY_S)) leftPaddle.y += paddleSpeed * dt;
			if (IsKeyDown(KEY_UP)) rightPaddle.y -= paddleSpeed * dt;
			if (IsKeyDown(KEY_DOWN)) rightPaddle.y += paddleSpeed * dt;

			if (leftPaddle.y < 0) leftPaddle.y = 0;
			if (leftPaddle.y > 500) leftPaddle.y = 500;
			if (rightPaddle.y < 0) rightPaddle.y = 0;
			if (rightPaddle.y > 500) rightPaddle.y = 500;

			ballPOS.x += ballSpeed.x * dt;
			ballPOS.y += ballSpeed.y * dt;

			if (ballPOS.y - ballRadius <= 0 || ballPOS.y + ballRadius >= 600) {
				ballSpeed.y *= -1;
			}

			if (CheckCollisionCircleRec(ballPOS, ballRadius, leftPaddle) || CheckCollisionCircleRec(ballPOS, ballRadius, rightPaddle)) {
				ballSpeed.x *= -1;
			}

			if (ballPOS.x + ballRadius < 0) {
				rightScore++;
				ballPOS = { 400, 300 };
				ballSpeed.x *= -1;
			}

			if (ballPOS.x - ballRadius > 800) {
				leftScore++;
				ballPOS = { 400, 300 };
				ballSpeed.x *= -1;
			}
		}
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText(TextFormat("%i", leftScore), 200, 30, 50, WHITE);
		DrawText(TextFormat("%i", rightScore), 600, 30, 50, WHITE);
		DrawLine(400, 0, 400, 600, DARKGRAY);
		DrawRectangleRec(leftPaddle, WHITE);
		DrawRectangleRec(rightPaddle, WHITE);
		DrawCircleV(ballPOS, ballRadius, WHITE);
		if (pauseGame) {
			DrawRectangle(0, 250, 800, 100, Fade(WHITE, 0.7f));
			DrawText("PAUSED", (800 - MeasureText("PAUSED", 50)) / 2, 275, 50, YELLOW);
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}