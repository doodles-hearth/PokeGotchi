Tamatown_MapScripts::
	.byte 0


Tamatown_EventScript_Porygon::
# 9 "data/maps/Tamatown/scripts.pory"
	lockall
# 11 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_PACHINKO, Tamatown_EventScript_Porygon_2
# 22 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_PACHINKO
# 24 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 25 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 26 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_2
# 33 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Porygon_1:
# 36 "data/maps/Tamatown/scripts.pory"
	goto_if_unset FLAG_RECEIVED_PACHINKO_COINS, Tamatown_EventScript_Porygon_6
Tamatown_EventScript_Porygon_5:
# 50 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Porygon_Text_4, Tamatown_EventScript_Porygon_Text_5
# 55 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 56 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_Porygon_10
# 84 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_WEAK
# 85 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 86 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_7
# 91 "data/maps/Tamatown/scripts.pory"
	closemessage
# 93 "data/maps/Tamatown/scripts.pory"
	releaseall
	return

Tamatown_EventScript_Porygon_2:
# 12 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 13 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Porygon_Movement_0
# 15 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 17 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 18 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_1
	goto Tamatown_EventScript_Porygon_1

Tamatown_EventScript_Porygon_6:
# 37 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Porygon_Text_3
# 40 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 41 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 43 "data/maps/Tamatown/scripts.pory"
	addcoins 15
# 45 "data/maps/Tamatown/scripts.pory"
	closemessage
# 47 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_PACHINKO_COINS
	goto Tamatown_EventScript_Porygon_5

Tamatown_EventScript_Porygon_10:
# 57 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_HIGH_PITCH
# 58 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 59 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_6
# 62 "data/maps/Tamatown/scripts.pory"
	closemessage
# 64 "data/maps/Tamatown/scripts.pory"
	switch VAR_FACING
# 65 "data/maps/Tamatown/scripts.pory"
	case DIR_NORTH, Tamatown_EventScript_Porygon_14
# 67 "data/maps/Tamatown/scripts.pory"
	case DIR_SOUTH, Tamatown_EventScript_Porygon_15
# 69 "data/maps/Tamatown/scripts.pory"
	case DIR_EAST, Tamatown_EventScript_Porygon_16
Tamatown_EventScript_Porygon_12:
# 73 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 75 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 76 "data/maps/Tamatown/scripts.pory"
	delay 32
# 77 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 78 "data/maps/Tamatown/scripts.pory"
	waitstate
# 79 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 80 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 81 "data/maps/Tamatown/scripts.pory"
	releaseall
	end

Tamatown_EventScript_Porygon_14:
# 66 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_1
	goto Tamatown_EventScript_Porygon_12

Tamatown_EventScript_Porygon_15:
# 68 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_2
	goto Tamatown_EventScript_Porygon_12

Tamatown_EventScript_Porygon_16:
# 70 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_3
	goto Tamatown_EventScript_Porygon_12


Tamatown_EventScript_Tree::
# 97 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tree_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_Tangela::
# 104 "data/maps/Tamatown/scripts.pory"
	lock
# 106 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FOUND_TANGELA, Tamatown_EventScript_Tangela_2
# 114 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_2
# 118 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_3, Tamatown_EventScript_Tangela_Text_4
# 123 "data/maps/Tamatown/scripts.pory"
	closemessage
# 125 "data/maps/Tamatown/scripts.pory"
	delay 24
# 128 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 130 "data/maps/Tamatown/scripts.pory"
	waitse
# 133 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_5
# 137 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_6, Tamatown_EventScript_Tangela_Text_7
# 142 "data/maps/Tamatown/scripts.pory"
	closemessage
# 144 "data/maps/Tamatown/scripts.pory"
	delay 24
# 147 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 149 "data/maps/Tamatown/scripts.pory"
	waitse
# 152 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_8
# 153 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_9
# 157 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_10, Tamatown_EventScript_Tangela_Text_11
# 162 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 163 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_0
# 164 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 165 "data/maps/Tamatown/scripts.pory"
	waitse
# 167 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 168 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 169 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_12
# 175 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 177 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FOUND_TANGELA
Tamatown_EventScript_Tangela_1:
# 180 "data/maps/Tamatown/scripts.pory"
	closemessage
# 182 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Tangela_2:
# 107 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 108 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 109 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_1
# 112 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Tangela_1


Tamatown_EventScript_Sign::
# 186 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Sign_Text_0, MSGBOX_SIGN
	return


Tamatown_EventScript_Skitty::
	return


Tamatown_EventScript_Trashcan::
# 197 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Trashcan_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_TrubbishCan::
# 205 "data/maps/Tamatown/scripts.pory"
	lock
# 207 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_0
# 212 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TrubbishCan_Text_1, Tamatown_EventScript_TrubbishCan_Text_2
# 217 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_2
# 302 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_13
Tamatown_EventScript_TrubbishCan_1:
# 306 "data/maps/Tamatown/scripts.pory"
	closemessage
# 308 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TrubbishCan_2:
# 218 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_3
# 222 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_TrubbishCan_Text_4, Tamatown_EventScript_TrubbishCan_Text_5
# 227 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_6
# 264 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 265 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_TrubbishCan_Movement_1
# 266 "data/maps/Tamatown/scripts.pory"
	waitse
# 267 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 269 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_10
# 272 "data/maps/Tamatown/scripts.pory"
	closemessage
# 274 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 275 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 277 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 278 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 279 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 281 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_8
# 282 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_11
Tamatown_EventScript_TrubbishCan_5:
# 291 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT
# 293 "data/maps/Tamatown/scripts.pory"
	setspeaker NULL
# 294 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 295 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_12
# 298 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 299 "data/maps/Tamatown/scripts.pory"
	closemessage
# 300 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_TEMP_1
	goto Tamatown_EventScript_TrubbishCan_1

Tamatown_EventScript_TrubbishCan_6:
# 228 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 0
# 229 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 3
# 230 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 4
# 231 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 232 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 233 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 234 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_6
# 235 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_7
# 239 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 240 "data/maps/Tamatown/scripts.pory"
	closemessage
# 242 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 243 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_0
# 244 "data/maps/Tamatown/scripts.pory"
	waitse
# 245 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 247 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 248 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 250 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 251 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 252 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 254 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_8
# 255 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_9
	goto Tamatown_EventScript_TrubbishCan_5


Tamatown_EventScript_Slowpoke::
# 312 "data/maps/Tamatown/scripts.pory"
	lock
# 314 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_RESTAURANT, Tamatown_EventScript_Slowpoke_2
# 324 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_RESTAURANT
# 326 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 327 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 328 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_2
Tamatown_EventScript_Slowpoke_1:
# 340 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Slowpoke_Text_3, Tamatown_EventScript_Slowpoke_Text_4
# 345 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Slowpoke_6
# 354 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_FAINT
# 355 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 356 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_6
Tamatown_EventScript_Slowpoke_5:
# 363 "data/maps/Tamatown/scripts.pory"
	closemessage
# 365 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Slowpoke_2:
# 315 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 316 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 317 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_1
	goto Tamatown_EventScript_Slowpoke_1

Tamatown_EventScript_Slowpoke_6:
# 346 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_HIGH_PITCH
# 347 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 348 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_5
	goto Tamatown_EventScript_Slowpoke_5


# 13 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_0:
# 13 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
	step_end

# 66 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_1:
# 66 "data/maps/Tamatown/scripts.pory"
	walk_right
# 66 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 68 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_2:
# 68 "data/maps/Tamatown/scripts.pory"
	walk_left
# 68 "data/maps/Tamatown/scripts.pory"
	walk_down
# 68 "data/maps/Tamatown/scripts.pory"
	walk_down
# 68 "data/maps/Tamatown/scripts.pory"
	walk_right
# 68 "data/maps/Tamatown/scripts.pory"
	walk_right
# 68 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 70 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_3:
# 70 "data/maps/Tamatown/scripts.pory"
	walk_down
# 70 "data/maps/Tamatown/scripts.pory"
	walk_right
# 70 "data/maps/Tamatown/scripts.pory"
	walk_right
# 70 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 163 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_0:
# 163 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
# 163 "data/maps/Tamatown/scripts.pory"
	delay_16
# 163 "data/maps/Tamatown/scripts.pory"
	delay_16
# 163 "data/maps/Tamatown/scripts.pory"
	delay_16
# 163 "data/maps/Tamatown/scripts.pory"
	delay_16
# 163 "data/maps/Tamatown/scripts.pory"
	delay_16
# 163 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 251 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_0:
# 251 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 251 "data/maps/Tamatown/scripts.pory"
	delay_16
# 251 "data/maps/Tamatown/scripts.pory"
	delay_16
# 251 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 265 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_1:
# 265 "data/maps/Tamatown/scripts.pory"
	emote_heart
# 265 "data/maps/Tamatown/scripts.pory"
	delay_16
# 265 "data/maps/Tamatown/scripts.pory"
	delay_16
# 265 "data/maps/Tamatown/scripts.pory"
	delay_16
# 265 "data/maps/Tamatown/scripts.pory"
	delay_16
# 265 "data/maps/Tamatown/scripts.pory"
	delay_16
# 265 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

Tamatown_EventScript_Porygon_Text_0:
# 17 "data/maps/Tamatown/scripts.pory"
	.string "Porygon$"

Tamatown_EventScript_Porygon_Text_1:
# 19 "data/maps/Tamatown/scripts.pory"
	.string "Yooo, my man's back!\nWanna play {COLOR RED}PACHINKO{COLOR DARK_GRAY}??\p$"

Tamatown_EventScript_Porygon_Text_2:
# 27 "data/maps/Tamatown/scripts.pory"
	.string "Yo, my man, come over here…\p"
	.string "Wanna try your luck at the most fun\nway to lose money ever invented?\l"
	.string "That's right, {COLOR RED}PACHINKO{COLOR DARK_GRAY}!!\p"
	.string "A game costs 3 coins.\nI'll give you 15 coins everyday!\p"
	.string "What are the coins for? Uhh…\nThey look super neat!$"

Tamatown_EventScript_Porygon_Text_3:
# 38 "data/maps/Tamatown/scripts.pory"
	.string "You got 15 coins!$"

Tamatown_EventScript_Porygon_Text_4:
# 51 "data/maps/Tamatown/scripts.pory"
	.string "I wanna play!$"

Tamatown_EventScript_Porygon_Text_5:
# 52 "data/maps/Tamatown/scripts.pory"
	.string "Nah.$"

Tamatown_EventScript_Porygon_Text_6:
# 60 "data/maps/Tamatown/scripts.pory"
	.string "Heck yeah! Have fun!$"

Tamatown_EventScript_Porygon_Text_7:
# 87 "data/maps/Tamatown/scripts.pory"
	.string "Aight, aight, can't help ya if you\nhate fun…$"

Tamatown_EventScript_Tree_Text_0:
# 98 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.\nIt kinda looks like your cousin Mark.$"

Tamatown_EventScript_Tangela_Text_0:
# 108 "data/maps/Tamatown/scripts.pory"
	.string "Tangela$"

Tamatown_EventScript_Tangela_Text_1:
# 110 "data/maps/Tamatown/scripts.pory"
	.string "Don't look at me!\nI am invisible!$"

Tamatown_EventScript_Tangela_Text_2:
# 115 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.$"

Tamatown_EventScript_Tangela_Text_3:
# 119 "data/maps/Tamatown/scripts.pory"
	.string "Yep$"

Tamatown_EventScript_Tangela_Text_4:
# 120 "data/maps/Tamatown/scripts.pory"
	.string "Totes$"

Tamatown_EventScript_Tangela_Text_5:
# 134 "data/maps/Tamatown/scripts.pory"
	.string "The tree moved impatiently.$"

Tamatown_EventScript_Tangela_Text_6:
# 138 "data/maps/Tamatown/scripts.pory"
	.string "Hmm.$"

Tamatown_EventScript_Tangela_Text_7:
# 139 "data/maps/Tamatown/scripts.pory"
	.string "Ahem.$"

Tamatown_EventScript_Tangela_Text_8:
# 152 "data/maps/Tamatown/scripts.pory"
	.string "Tree$"

Tamatown_EventScript_Tangela_Text_9:
# 154 "data/maps/Tamatown/scripts.pory"
	.string "{FONT_SMALL}Hee hee hee hee…{FONT_NORMAL}$"

Tamatown_EventScript_Tangela_Text_10:
# 158 "data/maps/Tamatown/scripts.pory"
	.string "Were you hiding?$"

Tamatown_EventScript_Tangela_Text_11:
# 159 "data/maps/Tamatown/scripts.pory"
	.string "I can see you$"

Tamatown_EventScript_Tangela_Text_12:
# 170 "data/maps/Tamatown/scripts.pory"
	.string "What? Oh, man!\p"
	.string "I was trying out my new “hiding in\nplain sight” secret technique…\l"
	.string "But you saw right through me!\p"
	.string "You must be some kind of genius!$"

Tamatown_EventScript_Sign_Text_0:
# 188 "data/maps/Tamatown/scripts.pory"
	.string "“6 Week Course: How To Manipulate\nYour Human Through Pooping”$"

Tamatown_EventScript_Trashcan_Text_0:
# 198 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "As hungry as it makes you, you need\nto go.$"

Tamatown_EventScript_TrubbishCan_Text_0:
# 208 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "…Wait a second…\nDid the trashcan just move?$"

Tamatown_EventScript_TrubbishCan_Text_1:
# 213 "data/maps/Tamatown/scripts.pory"
	.string "It did!$"

Tamatown_EventScript_TrubbishCan_Text_2:
# 214 "data/maps/Tamatown/scripts.pory"
	.string "I'm imagining things.$"

Tamatown_EventScript_TrubbishCan_Text_3:
# 219 "data/maps/Tamatown/scripts.pory"
	.string "What to do?$"

Tamatown_EventScript_TrubbishCan_Text_4:
# 223 "data/maps/Tamatown/scripts.pory"
	.string "Kick it.$"

Tamatown_EventScript_TrubbishCan_Text_5:
# 224 "data/maps/Tamatown/scripts.pory"
	.string "Hug it.$"

Tamatown_EventScript_TrubbishCan_Text_6:
# 234 "data/maps/Tamatown/scripts.pory"
	.string "Trashcan?$"

Tamatown_EventScript_TrubbishCan_Text_7:
# 236 "data/maps/Tamatown/scripts.pory"
	.string "WAIT! WAIT! STOP!$"

Tamatown_EventScript_TrubbishCan_Text_8:
# 254 "data/maps/Tamatown/scripts.pory"
	.string "Trubbish$"

Tamatown_EventScript_TrubbishCan_Text_9:
# 256 "data/maps/Tamatown/scripts.pory"
	.string "Whew! You almost got me there!\nNo, I wasn't hiding…\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_10:
# 270 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks… happy?$"

Tamatown_EventScript_TrubbishCan_Text_11:
# 283 "data/maps/Tamatown/scripts.pory"
	.string "I-I've never been held with such\nkindness before…\p"
	.string "Thanks, buddy.\nI'm happy you don't think I'm trash!\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_12:
# 296 "data/maps/Tamatown/scripts.pory"
	.string "You got the Doughnut!$"

Tamatown_EventScript_TrubbishCan_Text_13:
# 303 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks saddened.$"

Tamatown_EventScript_Slowpoke_Text_0:
# 316 "data/maps/Tamatown/scripts.pory"
	.string "Slowpoke$"

Tamatown_EventScript_Slowpoke_Text_1:
# 318 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Heeeeeeeeyyyyy…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_2:
# 329 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "… … … … … … …\p"
	.string "We opened up our restaurant\nreeeeecently… Buuuut…\p"
	.string "Customers don't tiiiiiiiip…\p"
	.string "They say the service is too sloooow…\p"
	.string "Can you belieeeeve it?\p"
	.string "You look faaaaast enouuuuuugh…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_3:
# 341 "data/maps/Tamatown/scripts.pory"
	.string "For sure!$"

Tamatown_EventScript_Slowpoke_Text_4:
# 342 "data/maps/Tamatown/scripts.pory"
	.string "Sounds tiring…$"

Tamatown_EventScript_Slowpoke_Text_5:
# 349 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Yaaaaaaaaaaaaaaaaaaay…$"

Tamatown_EventScript_Slowpoke_Text_6:
# 357 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "I understaaaand…\p"
	.string "It's suuuuuper tiiiiiiring…$"
