#pragma once
static const int WIDTH      = 512;
static const int HEIGHT     = 720;

enum class PlayerState
{
    ALIVE   = 0,
    DEAD,
};

static const float VELOCITY_X = 5.f;
static const float VELOCITY_Y = 5.f;

static const float TIME_STEP  = 0.01f;

