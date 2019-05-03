/*
** i_specialpaths.cpp
** Gets special system folders where data should be stored. (Switch version)
**
**---------------------------------------------------------------------------
** Copyright 2013-2016 Randy Heit
** Copyright 2016 Christoph Oelckers
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**---------------------------------------------------------------------------
**
*/

#include <sys/stat.h>
#include <sys/types.h>
#include "i_system.h"
#include "cmdlib.h"
#include "doomerrors.h"

#include "version.h"	// for GAMENAME


FString GetUserFile (const char *file)
{
	FString path;
	struct stat info;

	path = NicePath("/switch/" GAME_DIR "/");

	if (stat (path, &info) == -1)
		I_FatalError ("/switch/" GAME_DIR "/ does not exist");
	else if (!S_ISDIR(info.st_mode))
		I_FatalError ("%s must be a directory", path.GetChars());

	path += file;
	return path;
}

//===========================================================================
//
// M_GetAppDataPath														Unix
//
// Returns the path for the AppData folder.
//
//===========================================================================

FString M_GetAppDataPath(bool create)
{
	FString path = NicePath("/switch/" GAMENAMELOWERCASE);
	if (create)
	{
		CreatePath(path);
	}
	return path;
}

//===========================================================================
//
// M_GetCachePath														Unix
//
// Returns the path for cache GL nodes.
//
//===========================================================================

FString M_GetCachePath(bool create)
{
	FString path = NicePath("/switch/" GAME_DIR "/cache");
	if (create)
	{
		CreatePath(path);
	}
	return path;
}

//===========================================================================
//
// M_GetAutoexecPath													Unix
//
// Returns the expected location of autoexec.cfg.
//
//===========================================================================

FString M_GetAutoexecPath()
{
	return GetUserFile("autoexec.cfg");
}

//===========================================================================
//
// M_GetCajunPath														Unix
//
// Returns the location of the Cajun Bot definitions.
//
//===========================================================================

FString M_GetCajunPath(const char *botfilename)
{
	FString path;

	// Check first in $HOME/.config/zdoom/botfilename.
	path = GetUserFile(botfilename);
	if (!FileExists(path))
	{
		// Then check in SHARE_DIR/botfilename.
		path = SHARE_DIR;
		path << botfilename;
		if (!FileExists(path))
		{
			path = "";
		}
	}
	return path;
}

//===========================================================================
//
// M_GetConfigPath														Unix
//
// Returns the path to the config file. On Windows, this can vary for reading
// vs writing. i.e. If $PROGDIR/zdoom-<user>.ini does not exist, it will try
// to read from $PROGDIR/zdoom.ini, but it will never write to zdoom.ini.
//
//===========================================================================

FString M_GetConfigPath(bool for_reading)
{
	return GetUserFile(GAMENAMELOWERCASE ".ini");
}

//===========================================================================
//
// M_GetScreenshotsPath													Unix
//
// Returns the path to the default screenshots directory.
//
//===========================================================================

FString M_GetScreenshotsPath()
{
	return NicePath("/switch/" GAME_DIR "/screenshots/");
}

//===========================================================================
//
// M_GetSavegamesPath													Unix
//
// Returns the path to the default save games directory.
//
//===========================================================================

FString M_GetSavegamesPath()
{
	return NicePath("/switch/" GAME_DIR "/save");
}

//===========================================================================
//
// M_GetDocumentsPath												Unix
//
// Returns the path to the default documents directory.
//
//===========================================================================

FString M_GetDocumentsPath()
{
	return NicePath("/switch/" GAME_DIR);
}
