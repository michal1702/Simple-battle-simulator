#pragma once

#include "AssetManager.h"
#include "../Engine/AudioManager.h"

namespace RiD
{
	class Movement
	{
	private:
		struct animationDuration
		{
			sf::Time walking_animation_start_time;
			sf::Time walking_animation_frame_duration;
			sf::Time sword_animation_start_time;
			sf::Time sword_animation_frame_duration;
			sf::Time bow_shot_animation_start_time;
			sf::Time bow_shot_animation_frame_duration;
			sf::Time death_animation_start_time;
			sf::Time death_animation_frame_duration;
			sf::Time spear_animation_start_time;
			sf::Time spear_animation_frame_duration;
		};
		animationDuration animations;
		RiD::AudioManager _audio_manager;
		bool _is_attack_triggered, _is_shot_triggered, _is_death_triggered, _is_spear_triggered;
		short _row, _xCord, _yCord, _direction, _xAttackCord,
			_yAttackCord, _xshotCord, _yShotCord, _yDeathCord, _xDeathCord, _ySpearCord, _xSpearCord;
		enum directions { up, left, down, right };
		enum rowsInPNGFile { walkUpAnim = 8, walkLeftAnim, walkDownAnim, walkRightAnim, shotAnim = 16, deathAnim = 20, swordSwingAnim };
		sf::Texture _texture;
		sf::Sprite* _object;

		bool _ready_to_deal_sword_damage, _ready_to_shot_arrow, _ready_to_deal_spear_damage;
	public:
		Movement(sf::Texture texture, sf::Sprite*& object);

		///Walking up animation
		void walkingUp(sf::Time time, float speed_x, float speed_y);

		///Walking down animation
		void walkingDown(sf::Time time, float speed_x, float speed_y);

		///Walking left animation
		void walkingLeft(sf::Time time, float speed_x, float speed_y);

		///Walking right animation
		void walkingRight(sf::Time time, float speed_x, float speed_y);

		///Sword attack
		void swordSwing(sf::Time time);

		///Spear attack
		void spearPoke(sf::Time time);

		///Bow attack
		void bowShot(sf::Time time, short direction);

		///Standing
		void idle(sf::Time time);

		///Lying dead
		void dead();

		///Death animation
		void death(sf::Time time);

		///Function triggers spear attack
		void triggerSpear();

		///Function triggers sword attack
		void triggerAttack();

		///Function triggers bow shot
		void triggerShot();

		///Function triggers death
		void triggerDeath();

		///@return is spear attack animation triggered
		bool isSpearTriggered();

		///@return is sword attack animation triggered
		bool isAttackTriggered();

		///@return is shot animation triggered
		bool isShotTriggered();

		///@return is death animation triggered
		bool isDeathTriggered();

		///Checks if previous animation stopped
		bool isReadyToDealSpearDamage();

		///Checks if previous animation stopped
		bool isReadyToDealSwordDamage();

		///Set not ready
		void notReadyToDealSpearDamage();

		///Set not ready
		void notReadyToDealSwordDamage();

		///Checks if previous animation stopped
		bool isReadyToShotArrow();

		///Set not ready
		void notReadyToShotArrow();

		///Returns sprite
		sf::Sprite getSprite();

		///@return character direction
		short getDirection();

		///Sets sprite position
		void setSpritePosition(sf::Vector2f position);
	};
}