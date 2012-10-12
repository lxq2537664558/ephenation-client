// Copyright 2012 The Ephenation Authors
//
// This file is part of Ephenation.
//
// Ephenation is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.
//
// Ephenation is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Ephenation.  If not, see <http://www.gnu.org/licenses/>.
//

#pragma once

#include <memory>

#include "ui/mainuserinterface.h"
#include "rendercontrol.h"

using std::string;

struct chunk;
struct ChunkOffsetCoord;
struct ChunkCoord;
class Object;
class ChunkShader;
class BuildingBlocks;
class HealthBar;
class DrawTexture;

namespace Rocket {
	namespace Core {
		class Context; // Lots of work to forward declare this
	}
};

// Put it all together. Manage, on a high level:
// * keyboard input
// * mouse input
// * decide what shall be shown on the screen
// * window resize events
// * a few special effects (zooming)
// * manage construction of activator blocks
//
// TODO: This class has grown to be rather fat. A refactoring is needed.
class gameDialog {
public:
	gameDialog();
	virtual void render();
	virtual void init();
	virtual ~gameDialog();
	virtual void handleMouse(int button, int action);
	virtual void Update();
	virtual void SetMessage(const char *);
	virtual void HandleKeyRelease(int key); // Keyboard event
	virtual void HandleKeyPress(int key);	// Keyboard event
	virtual void HandleCharacter(int key, int action);	// Character event
	virtual void handleResize(int w, int h);
	void handleMouseActiveMotion(int x, int y);

	void ClickOnBlock(int x, int y);
	void ClickOnObject(int x, int y);
	void AttachBlockToSurface(int row, int col);
	void ClearSelection(void); // Clear the selected object
	void AggroFrom(Object *); // The player now has aggro from this monster
	// Notification that there are new messages available.
	void NotifyMessage(void);
	enum Calibration { CALIB_EXPOSURE, CALIB_WHITE_POINT, CALIB_AMBIENT, CALIB_NONE };
	void CalibrateMode(Calibration);

	bool ThirdPersonView(void) const { return fCameraDistance > 2.0f; }

	// Manage the running status of the player
	void UpdateRunningStatus(bool disable);

	static gameDialog *sfCurrentGameDialog;

	bool fShowInventory;

	// Define possible effects that can be requested. They will all terminate automatically.
	enum Effect {
		EFFECT_NONE,  // Normal mode, no special effects.
		EFFECT_ZOOM1, // Zoom from normal view to half viewing angle in 0.5s
		EFFECT_ZOOM2  // Zoom from 120 degrees viewing angle to normal angle in 0.5s
	};
	void RequestEffect(Effect eff);
	void CancelCurrentEffect(void);
	void UpdateEffect(void);

private:
	Effect fCurrentEffect;
	bool fMovingFwd;
	bool fMovingBwd;
	bool fMovingLeft;
	bool fMovingRight;
	bool fUsingTorch;
	float fCameraDistance; // Actual camera distance behind the player
	float fRequestedCameraDistance;
	int fMapWidth;
	Calibration fCalibrationMode;

	bool fEnterDebugText;
	bool fDrawMap;
	bool fShowWeapon;
	bool fShowMainDialog;
	bool fHideDialog; // This will override the fShowMainDialog.
	bool fUnderWater; // True when player is below water
	unsigned char fDebugText[1000]; // TODO: use std::string
	unsigned int fDebugTextLength;
	chunk *FindSelectedSurface(int x, int y, ChunkOffsetCoord *, int *surfaceDir);
	Object *FindSelectedObject(int x, int y);
	void DrawPlayerStats(void) const;
	void DrawWeapon(void) const;
	void DrawHealingAnimation(bool restart) const; // Draw a healing animation
	void DrawCompassRose(void) const;
	void UpdateCameraPosition(void); // Check if camera position is inside a wall
	// Call this when a dialog will be showed, to stop movement, etc. All key presses will be
	// henceforth be forwarded to the dialog, and the player can't stop moving.
	void ClearForDialog(void);
	Object *fSelectedObject; // Pointer to the object (monster, player, ...) that is selected
	GLuint fFPSsentence;
	GLuint fInputPromptSentence;
	GLuint fPlayerStatusSentence;
	ChunkShader *fShader;
	BuildingBlocks *fBuildingBlocks;
	HealthBar *fHealthBar;
	DrawTexture *fDrawTexture;
	RenderControl fRenderControl;

	// All keyboard and mouse events are redirected to this one if it is non-null
	Rocket::Core::Context *fCurrentRocketContextInput;

	MainUserInterface fMainUserInterface;
	Rocket::Core::Element *fFPS_Element, *fPlayerStatsOneLiner_Element;
};

extern gameDialog gGameDialog;
extern float renderViewAngle;

// Save the place where a text activator was requested.
extern ChunkCoord gRequestActivatorChunk;
extern int gRequestActivatorX, gRequestActivatorY, gRequestActivatorZ;

// A string that automatically will be shown in a pop up window.
extern string sgPopup;
extern string sgPopupTitle; // Use this title in the next popup message window.