#pragma once


#define SCREEN_WIDTH					   500
#define SCREEN_HEIGHT					   600
										   
#define SPLASH_STATE_SHOW_TIME			   5.0f
#define TIME_BEFORE_GAME_OVER			   2.0f
										   
#define BIRD_WIDTH						   40
#define BIRD_HEIGHT						   28

#define BIRD_ANIMATION_DURATION            0.2f
#define MARIO_ANIMATION_DURATION           0.5f
#define TIME_MARIO_FIRE                    0.2f
#define TIME_MARIO_VISIBLE                 5.0f
#define BULLET_ANIMATION_DURATION          0.2f


#define FLYING_SPEED					   200.0f
#define GRAVITY_SPEED					   13.0f

#define ROTATION_SPEED					   100.0f										   
#define FLYING_DURATION					   0.1f

										   
#define PIPE_MOVEMENT_SPEED				   200.0f
#define PIPE_SPAWN_FREQUENCY			   1.5f
										   
#define BULLET_SPEED					   300.0f										   
#define FLASH_SPEED						   2000.0f
#define FLASH_TIMES						   2
#define LAND_COORD_Y                       450.0f
#define HIGH_SCORE_FILEPATH                "HighScore.txt"
#define BRONZE_SCORE					   0
#define SILVER_SCORE					   10
#define GOLD_SCORE						   30
#define PLATINUM_SCORE				       50

enum BIRD_STATE
{
	eFALLING,
	eFLYING
};

enum GAME_STATES
{
	eREADY,
	ePLAYING,
	eGAMEOVER
	
};

#define SPLASH_SCENE_BACKGROUND_FILEPATH "Assets/res/Splash.png"

#define MAIN_MENU_BACKGROUND_FILEPATH    "Assets/res/sky.png"
#define GAME_BACKGROUND_FILEPATH		 "Assets/res/sky.png"
#define GAME_READY_FILEPATH				 "Assets/res/ready.png"
#define GAME_OVER_BACKGROUND_FILEPATH	 "Assets/res/sky.png"
#define GAME_OVER_TITLE_FILEPATH		 "Assets/res/Game-Over-Title.png"
#define GAME_OVER_BODY_FILEPATH			 "Assets/res/Game-Over-Body.png"

#define GAME_TITLE_FILEPATH				 "Assets/res/Title.png"
#define PLAY_BUTTON_FILEPATH			 "Assets/res/PlayButton.png"

#define BIRD_FRAME_1_FILEPATH			 "Assets/res/Bird/bird-anim-01.png"
#define BIRD_FRAME_2_FILEPATH			 "Assets/res/Bird/bird-anim-02.png"
#define BIRD_FRAME_3_FILEPATH			 "Assets/res/Bird/bird-anim-03.png"
#define BIRD_FRAME_4_FILEPATH			 "Assets/res/Bird/bird-anim-04.png"
#define BIRD_DIE_FILEPATH				 "Assets/res/Bird/bird-die-01.png"

#define PIPE_UP_FILEPATH				 "Assets/res/Pipes/PipeUp.png"
#define PIPE_DOWN_FILEPATH				 "Assets/res/Pipes/PipeDown.png"


#define PIPE_SCORING_FILEPATH			 "Assets/res/Pipes/InvisibleScoringPipe.png"

#define MARIO_FRAME_1_FILEPATH           "Assets/res/Mario/mario-idle.png"
#define MARIO_FRAME_2_FILEPATH           "Assets/res/Mario/mario-fire-1.png"
#define MARIO_FRAME_3_FILEPATH           "Assets/res/Mario/mario-fire-2.png"

#define BULLET_FRAME_1_FILEPATH			 "Assets/res/Bullets/bullet-1.png"
#define BULLET_FRAME_2_FILEPATH			 "Assets/res/Bullets/bullet-2.png"
#define BULLET_EX_1_FILEPATH			 "Assets/res/Bullets/explosion-1.png"
#define BULLET_EX_2_FILEPATH			 "Assets/res/Bullets/explosion-2.png"
#define BULLET_EX_3_FILEPATH			 "Assets/res/Bullets/explosion-3.png"

#define LAND_FILEPATH					 "Assets/res/land.png"

#define FONT_FILEPATH					 "Assets/fonts/FlappyFont.ttf"
#define BRONZE_MEDAL_FILEPATH            "Assets/res/Medals/Bronze-Medal.png"
#define SILVER_MEDAL_FILEPATH            "Assets/res/Medals/Silver-Medal.png"
#define GOLD_MEDAL_FILEPATH              "Assets/res/Medals/Gold-Medal.png"
#define PLATINUM_MEDAL_FILEPATH          "Assets/res/Medals/Platinum-Medal.png"

#define HIT_SOUND_FILEPATH				 "Assets/audio/Hit.wav"
#define POINT_SOUND_FILEPATH			 "Assets/audio/Point.wav"
#define WING_SOUND_FILEPATH				 "Assets/audio/Wing.wav"
#define FIRE_BALL_SOUND_FILEPATH		 "Assets/audio/FireBall.wav"