/* OpenCP Module Player
 * copyright (c) 1994-'10 Niklas Beisert <nbeisert@physik.tu-muenchen.de>
 * copyright (c) 2005-'22 Stian Skjelstad <stian.skjelstad@gmail.com>
 *
 * Timidity channel viewer interface
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "config.h"
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "dev/mcp.h"
#include "timidityplay.h"
#include "stuff/poutput.h"
#include "cpiface/cpiface.h"
#include "timidity-git/timidity/timidity.h"

extern struct timiditycontext_t tc;
#define midGetMute(i) IS_SET_CHANNELMASK(tc.channel_mute, i)

static void drawchannel36 (struct cpifaceSessionAPI_t *cpifaceSession, uint16_t *buf, int i)
{
	struct mchaninfo ci;
	unsigned char mute=midGetMute(i);

	unsigned char tcol=mute?0x08:0x0F;
	unsigned char tcold=mute?0x08:0x07;
/*
	unsigned char tcolr=mute?0x08:0x0B;*/

	int j;

	timidityGetChanInfo(i, &ci);

	writestring(buf, 0, tcold, " -- -- -. \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa   ", 36);

	if (!ci.notenum)
		return;
	writenum(buf,  1, tcol, ci.program, 16, 2, 0);
	writenum(buf, 4, tcol, ci.gvol, 16, 2, 0);
	writestring(buf,  7, tcol, &"L123456MM9ABCDER"[ci.pan>>3], 1);
	writestring(buf,  8, tcol, &" P"[ci.pedal], 1);
	if (ci.notenum>6)
		ci.notenum=6;
	for (j=0; j<ci.notenum; j++)
		writestring(buf, 10+4*j, (ci.opt[j]&1)?tcol:0x08, plNoteStr[ci.note[j]+12], 3);
}

static void drawchannel62 (struct cpifaceSessionAPI_t *cpifaceSession, uint16_t *buf, int i)
{
	struct mchaninfo ci;
	unsigned char mute=midGetMute(i);

	unsigned char tcol=mute?0x08:0x0F;
	unsigned char tcold=mute?0x08:0x07;
/*
	unsigned char tcolr=mute?0x08:0x0B;*/

	int j;

	timidityGetChanInfo(i, &ci);

	writestring(buf, 0, tcold, "                  -- -. \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa ", 62);

	if (!ci.notenum)
		return;
	writestring(buf,  1, tcol, ci.instrument, 16);
	writenum(buf, 18, tcol, ci.gvol, 16, 2, 0);
	writestring(buf,  21, tcol, &"L123456MM9ABCDER"[ci.pan>>3], 1);
	writestring(buf,  22, tcol, &" P"[ci.pedal], 1);
	if (ci.notenum>9)
		ci.notenum=9;
	for (j=0; j<ci.notenum; j++)
		writestring(buf, 24+4*j, (ci.opt[j]&1)?tcol:0x08, plNoteStr[ci.note[j]+12], 3);
}

static void drawchannel76 (struct cpifaceSessionAPI_t *cpifaceSession, uint16_t *buf, int i)
{
	struct mchaninfo ci;
	unsigned char mute=midGetMute(i);

	unsigned char tcol=mute?0x08:0x0F;
	unsigned char tcold=mute?0x08:0x07;
/*
	unsigned char tcolr=mute?0x08:0x0B;*/

	int j;

	timidityGetChanInfo(i, &ci);

	writestring(buf, 0, tcold, "               \xfa  \xfa \xfa \xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa", 76);

	if (!ci.notenum)
		return;
	writestring(buf,  1, tcol, ci.instrument, 14);
	writenum(buf, 16, tcol, ci.gvol, 16, 2, 0);
	writestring(buf, 19, tcol, &"L123456MM9ABCDER"[ci.pan>>3], 1);
	if (ci.notenum>7)
		ci.notenum=7;
	for (j=0; j<ci.notenum; j++)
	{
		writestring(buf, 22+8*j, (ci.opt[j]&1)?tcol:0x08, plNoteStr[ci.note[j]+12], 3);
		writenum(buf, 26+8*j, (ci.opt[j]&1)?tcold:0x08, ci.vol[j], 16, 2, 0);
	}
}

static void drawchannel128 (struct cpifaceSessionAPI_t *cpifaceSession, uint16_t *buf, int i)
{
	struct mchaninfo ci;
	unsigned char mute=midGetMute(i);

	unsigned char tcol=mute?0x08:0x0F;
	unsigned char tcold=mute?0x08:0x07;
/*
	unsigned char tcolr=mute?0x08:0x0B;*/

	int j;

	timidityGetChanInfo(i, &ci);

	writestring(buf, 0, tcold,
			"                  \xfa  \xfa \xfa     \xfa  \xfa  \xfa  \xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa"
			"  \xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa  "
			"\xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa  \xfa\xfa\xfa \xfa\xfa  ", 128);

	if (!ci.notenum)
		return;

	writestring(buf,  1, tcol, ci.instrument, 16);
	writenum(buf, 19, tcol, ci.gvol, 16, 2, 0);
	writestring(buf, 22, tcol, &"L123456MM9ABCDER"[ci.pan>>3], 1);
	writestring(buf, 24, tcol, (ci.pitch<0)?"-":(ci.pitch>0)?"+":" ", 1);
	writenum(buf, 25, tcol, abs(ci.pitch), 16, 4, 0);
	writenum(buf, 30, tcol, ci.reverb, 16, 2, 0);
	writenum(buf, 33, tcol, ci.chorus, 16, 2, 0);

	if (ci.notenum>11)
		ci.notenum=11;
	for (j=0; j<ci.notenum; j++)
	{
		writestring(buf, 38+8*j, (ci.opt[j]&1)?tcol:0x08, plNoteStr[ci.note[j]+12], 3);
		writenum(buf, 42+8*j, (ci.opt[j]&1)?tcold:0x08, ci.vol[j], 16, 2, 0);
	}
}

static void drawchannel44 (struct cpifaceSessionAPI_t *cpifaceSession, uint16_t *buf, int i)
{
	struct mchaninfo ci;
	unsigned char mute=midGetMute(i);

	unsigned char tcol=mute?0x08:0x0F;
	unsigned char tcold=mute?0x08:0x07;
/*
	unsigned char tcolr=mute?0x08:0x0B;*/

	int j;

	timidityGetChanInfo(i, &ci);

	writestring(buf, 0, tcold, " -- -- -. \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa \xfa\xfa\xfa   ", 44);

	if (!ci.notenum)
		return;

	writenum(buf,  1, tcol, ci.program, 16, 2, 0);
	writenum(buf, 4, tcol, ci.gvol, 16, 2, 0);
	writestring(buf,  7, tcol, &"L123456MM9ABCDER"[ci.pan>>3], 1);
	writestring(buf,  8, tcol, &" P"[ci.pedal], 1);

	if (ci.notenum>8)
		ci.notenum=8;
	for (j=0; j<ci.notenum; j++)
		writestring(buf, 10+4*j, (ci.opt[j]&1)?tcol:0x08, plNoteStr[ci.note[j]+12], 3);
}

static void drawchannel (struct cpifaceSessionAPI_t *cpifaceSession, uint16_t *buf, int len, int i)
{
	switch (len)
	{
		case 36:
			drawchannel36 (cpifaceSession, buf, i);
			break;
		case 44:
			drawchannel44 (cpifaceSession, buf, i);
			break;
		case 62:
			drawchannel62 (cpifaceSession, buf, i);
			break;
		case 76:
			drawchannel76 (cpifaceSession, buf, i);
			break;
		case 128:
			drawchannel128 (cpifaceSession, buf, i);
			break;
	}
}

void __attribute__ ((visibility ("internal"))) timidityChanSetup (struct cpifaceSessionAPI_t *cpifaceSession/*const struct midifile *mid*/)
{
	/*plChanMInstr=mid->instruments; TODO ?*/
	plUseChannels (cpifaceSession, drawchannel);
}
