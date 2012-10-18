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

#include <string>

using std::string;

class OptionsDialog;

class Options {
public:
	void Init(const std::string &fileName);

	static Options fgOptions;

	std::string fSavePath;

	// These are parameters initialized from the ini file
	std::string fEmail;
	std::string fLicenseKey;
	float fViewingDistance;
	float fCameraDistance; // Used for third person view
	float fWhitePoint; // The limit that shall be considered as white in the HDR image
	float fExposure;
	int fWindowWidth;
	int fWindowHeight;
	int fFontSize;
	int fMsgWinTransparency;
	int fMusicVolume;
	int fMusicOn;
	int fSoundFxVolume;
	int fEnableTestbutton;
	int fPerformance; // A value from 1 to 4.
	int fNewPerformance; // Next time, use this performance
	int fMaxLamps, fMaxShadows, fMaxFog;
	int fFullScreen;
	int fAmbientLight; // Going from 0 to 100
	int fSmoothTerrain;
	int fMergeNormals; // Merge normals in the terrain to make a smoother view
	int fAddNoise; // Add random terrain noise
	int fDynamicShadows;   // Use a shadowmap for dynamic shadow generation.
	int fStaticShadows;    // A simpler version of dynamic shadows.
	int fAnisotropicFiltering;
	int fVSYNC;
	unsigned fNumThreads; // Not really configurable

	void ListGraphicModes(OptionsDialog *) const;

	// Update all settings from an options dialog.
	void UpdateSettings(OptionsDialog *);

	void ParseOneOption(const string &key, const string &arg);
private:
	void Save(void) const; // Save the parsed data back to the file again
	Options(void);
	~Options(void);
	std::string fFileName;

	// When the general performance is changed, other options may change as a result. Don't call
	// this function unless the user actively changes the performance index.
	void UpdatePerformance(int perf);

};
