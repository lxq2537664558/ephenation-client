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

// This class manages the in-game dialog for options. Eventually, it will completely
// replace OptionsDialog.

#include "dialog.h"

class HelpDialog2 : public dialog {
public:
	HelpDialog2();

	// Draw the dialog background.
	virtual void Draw(DrawTexture *drawTexture, float alpha);

	// The player clicked on something. Return false if the windows is closed.
	virtual void Click(void);
private:
	DialogText fPrevious, fTitle, fBody;
	enum class ActiveElement { NONE, PREVIOUS };
	ActiveElement fActiveElement;
};
