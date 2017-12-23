// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "hook.h"
#include <Windows.h>
#include <stdio.h>

void placeHook(int trampoline_location, int target_location) {

	char jmp_inst[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
	int distance;
	DWORD dwProtect = 0;

	distance = target_location - trampoline_location - 5;

	// Write jump-distance to instruction
	memcpy((jmp_inst+1), &distance, 4);

	if (!VirtualProtect((LPVOID)trampoline_location, sizeof(jmp_inst), PAGE_EXECUTE_READWRITE, &dwProtect)) {
		perror("Failed to unprotect memory\n");
		return;
	}

	memcpy((LPVOID)trampoline_location, jmp_inst, sizeof(jmp_inst));

	VirtualProtect((LPVOID)trampoline_location, sizeof(jmp_inst),dwProtect, NULL);

}

void replaceOffset(int trampoline_location, int target_location) {

	char inst_offset[] = { 0x00, 0x00, 0x00, 0x00 };
	int distance;
	DWORD dwProtect = 0;

	int offset_location = trampoline_location + 1;

	distance = target_location - trampoline_location - 5;

	// Write jump-distance to instruction
	memcpy(inst_offset, &distance, 4);

	if (!VirtualProtect((LPVOID)offset_location, sizeof(inst_offset), PAGE_EXECUTE_READWRITE, &dwProtect)) {
		perror("Failed to unprotect memory\n");
		return;
	}

	memcpy((LPVOID)offset_location, inst_offset, sizeof(inst_offset));

	VirtualProtect((LPVOID)offset_location, sizeof(inst_offset),dwProtect, NULL);

}

void replaceAddr(int addr, int value) {
	DWORD dwProtect;

	if (!VirtualProtect((LPVOID)addr, sizeof(int), PAGE_EXECUTE_READWRITE, &dwProtect)) {
		perror("Failed to unprotect memory\n");
		return;
	}

	*((int*)addr) = value;

	VirtualProtect((LPVOID)addr, sizeof(int),dwProtect, NULL);
}