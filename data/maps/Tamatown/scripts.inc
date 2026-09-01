Tamatown_MapScripts::
	.byte 0


Tamatown_EventScript_Porygon::
# 9 "data/maps/Tamatown/scripts.pory"
	lockall
# 11 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 12 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_1
# 19 "data/maps/Tamatown/scripts.pory"
	closemessage
# 21 "data/maps/Tamatown/scripts.pory"
	goto_if_unset FLAG_RECEIVED_PACHINKO_COINS, Tamatown_EventScript_Porygon_2
Tamatown_EventScript_Porygon_1:
# 35 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Porygon_Text_3, Tamatown_EventScript_Porygon_Text_4
# 40 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 41 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_Porygon_6
# 68 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 69 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_6
# 74 "data/maps/Tamatown/scripts.pory"
	closemessage
# 76 "data/maps/Tamatown/scripts.pory"
	releaseall
	return

Tamatown_EventScript_Porygon_2:
# 22 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Porygon_Text_2
# 25 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 26 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 28 "data/maps/Tamatown/scripts.pory"
	addcoins 15
# 30 "data/maps/Tamatown/scripts.pory"
	closemessage
# 32 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_PACHINKO_COINS
	goto Tamatown_EventScript_Porygon_1

Tamatown_EventScript_Porygon_6:
# 42 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 43 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_5
# 46 "data/maps/Tamatown/scripts.pory"
	closemessage
# 48 "data/maps/Tamatown/scripts.pory"
	switch VAR_FACING
# 49 "data/maps/Tamatown/scripts.pory"
	case DIR_NORTH, Tamatown_EventScript_Porygon_10
# 51 "data/maps/Tamatown/scripts.pory"
	case DIR_SOUTH, Tamatown_EventScript_Porygon_11
# 53 "data/maps/Tamatown/scripts.pory"
	case DIR_EAST, Tamatown_EventScript_Porygon_12
Tamatown_EventScript_Porygon_8:
# 57 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 59 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 60 "data/maps/Tamatown/scripts.pory"
	delay 32
# 61 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 62 "data/maps/Tamatown/scripts.pory"
	waitstate
# 63 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 64 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 65 "data/maps/Tamatown/scripts.pory"
	releaseall
	end

Tamatown_EventScript_Porygon_10:
# 50 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_0
	goto Tamatown_EventScript_Porygon_8

Tamatown_EventScript_Porygon_11:
# 52 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_1
	goto Tamatown_EventScript_Porygon_8

Tamatown_EventScript_Porygon_12:
# 54 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_2
	goto Tamatown_EventScript_Porygon_8


Tamatown_EventScript_Tree::
# 80 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tree_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_Tangela::
# 87 "data/maps/Tamatown/scripts.pory"
	lock
# 89 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FOUND_TANGELA, Tamatown_EventScript_Tangela_2
# 97 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_2
# 101 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_3, Tamatown_EventScript_Tangela_Text_4
# 106 "data/maps/Tamatown/scripts.pory"
	closemessage
# 108 "data/maps/Tamatown/scripts.pory"
	delay 24
# 111 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 113 "data/maps/Tamatown/scripts.pory"
	waitse
# 116 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_5
# 120 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_6, Tamatown_EventScript_Tangela_Text_7
# 125 "data/maps/Tamatown/scripts.pory"
	closemessage
# 127 "data/maps/Tamatown/scripts.pory"
	delay 24
# 130 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 132 "data/maps/Tamatown/scripts.pory"
	waitse
# 135 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_8
# 136 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_9
# 140 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_10, Tamatown_EventScript_Tangela_Text_11
# 145 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 146 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_0
# 147 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 148 "data/maps/Tamatown/scripts.pory"
	waitse
# 150 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 151 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 152 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_12
# 158 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 160 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FOUND_TANGELA
Tamatown_EventScript_Tangela_1:
# 163 "data/maps/Tamatown/scripts.pory"
	closemessage
# 165 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Tangela_2:
# 90 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 91 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 92 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_1
# 95 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Tangela_1


Tamatown_EventScript_Sign::
# 169 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Sign_Text_0, MSGBOX_SIGN
	return


Tamatown_EventScript_Skitty::
	return


Tamatown_EventScript_Trashcan::
# 180 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Trashcan_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_TrubbishCan::
# 188 "data/maps/Tamatown/scripts.pory"
	lock
# 190 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_0
# 195 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TrubbishCan_Text_1, Tamatown_EventScript_TrubbishCan_Text_2
# 200 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_2
# 285 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_13
Tamatown_EventScript_TrubbishCan_1:
# 289 "data/maps/Tamatown/scripts.pory"
	closemessage
# 291 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TrubbishCan_2:
# 201 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_3
# 205 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_TrubbishCan_Text_4, Tamatown_EventScript_TrubbishCan_Text_5
# 210 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_6
# 247 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 248 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_TrubbishCan_Movement_1
# 249 "data/maps/Tamatown/scripts.pory"
	waitse
# 250 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 252 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_10
# 255 "data/maps/Tamatown/scripts.pory"
	closemessage
# 257 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 258 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 260 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 261 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 262 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 264 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_8
# 265 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_11
Tamatown_EventScript_TrubbishCan_5:
# 274 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT
# 276 "data/maps/Tamatown/scripts.pory"
	setspeaker NULL
# 277 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 278 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_12
# 281 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 282 "data/maps/Tamatown/scripts.pory"
	closemessage
# 283 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_TEMP_1
	goto Tamatown_EventScript_TrubbishCan_1

Tamatown_EventScript_TrubbishCan_6:
# 211 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 0
# 212 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 3
# 213 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 4
# 214 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 215 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 216 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 217 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_6
# 218 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_7
# 222 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 223 "data/maps/Tamatown/scripts.pory"
	closemessage
# 225 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 226 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_0
# 227 "data/maps/Tamatown/scripts.pory"
	waitse
# 228 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 230 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 231 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 233 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 234 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 235 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 237 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_8
# 238 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_9
	goto Tamatown_EventScript_TrubbishCan_5


Tamatown_EventScript_Slowpoke::
# 295 "data/maps/Tamatown/scripts.pory"
	lock
# 297 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 298 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 299 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_1
# 310 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Slowpoke_Text_2, Tamatown_EventScript_Slowpoke_Text_3
# 315 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Slowpoke_2
# 324 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_FAINT
# 325 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 326 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_5
Tamatown_EventScript_Slowpoke_1:
# 333 "data/maps/Tamatown/scripts.pory"
	closemessage
# 335 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Slowpoke_2:
# 316 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 317 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 318 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_4
	goto Tamatown_EventScript_Slowpoke_1


# 50 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_0:
# 50 "data/maps/Tamatown/scripts.pory"
	walk_right
# 50 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 52 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_1:
# 52 "data/maps/Tamatown/scripts.pory"
	walk_left
# 52 "data/maps/Tamatown/scripts.pory"
	walk_down
# 52 "data/maps/Tamatown/scripts.pory"
	walk_down
# 52 "data/maps/Tamatown/scripts.pory"
	walk_right
# 52 "data/maps/Tamatown/scripts.pory"
	walk_right
# 52 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 54 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_2:
# 54 "data/maps/Tamatown/scripts.pory"
	walk_down
# 54 "data/maps/Tamatown/scripts.pory"
	walk_right
# 54 "data/maps/Tamatown/scripts.pory"
	walk_right
# 54 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 146 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_0:
# 146 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
# 146 "data/maps/Tamatown/scripts.pory"
	delay_16
# 146 "data/maps/Tamatown/scripts.pory"
	delay_16
# 146 "data/maps/Tamatown/scripts.pory"
	delay_16
# 146 "data/maps/Tamatown/scripts.pory"
	delay_16
# 146 "data/maps/Tamatown/scripts.pory"
	delay_16
# 146 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 234 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_0:
# 234 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 234 "data/maps/Tamatown/scripts.pory"
	delay_16
# 234 "data/maps/Tamatown/scripts.pory"
	delay_16
# 234 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 248 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_1:
# 248 "data/maps/Tamatown/scripts.pory"
	emote_heart
# 248 "data/maps/Tamatown/scripts.pory"
	delay_16
# 248 "data/maps/Tamatown/scripts.pory"
	delay_16
# 248 "data/maps/Tamatown/scripts.pory"
	delay_16
# 248 "data/maps/Tamatown/scripts.pory"
	delay_16
# 248 "data/maps/Tamatown/scripts.pory"
	delay_16
# 248 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

Tamatown_EventScript_Porygon_Text_0:
# 11 "data/maps/Tamatown/scripts.pory"
	.string "Porygon$"

Tamatown_EventScript_Porygon_Text_1:
# 13 "data/maps/Tamatown/scripts.pory"
	.string "Yo, my man, come over here…\p"
	.string "Wanna try your luck at the most fun\nway to lose money ever invented?\l"
	.string "That's right, PACHINKO!!\p"
	.string "A game costs 3 coins.\nI'll give you 15 coins everyday!\p"
	.string "What are the coins for? Uhh…\nThey look super neat!$"

Tamatown_EventScript_Porygon_Text_2:
# 23 "data/maps/Tamatown/scripts.pory"
	.string "You got 15 coins!$"

Tamatown_EventScript_Porygon_Text_3:
# 36 "data/maps/Tamatown/scripts.pory"
	.string "I wanna play!$"

Tamatown_EventScript_Porygon_Text_4:
# 37 "data/maps/Tamatown/scripts.pory"
	.string "Nah.$"

Tamatown_EventScript_Porygon_Text_5:
# 44 "data/maps/Tamatown/scripts.pory"
	.string "Heck yeah! Have fun!$"

Tamatown_EventScript_Porygon_Text_6:
# 70 "data/maps/Tamatown/scripts.pory"
	.string "Aight, aight, can't help ya if you\nhate fun…$"

Tamatown_EventScript_Tree_Text_0:
# 81 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.\nIt kinda looks like your cousin Mark.$"

Tamatown_EventScript_Tangela_Text_0:
# 91 "data/maps/Tamatown/scripts.pory"
	.string "Tangela$"

Tamatown_EventScript_Tangela_Text_1:
# 93 "data/maps/Tamatown/scripts.pory"
	.string "Don't look at me!\nI am invisible!$"

Tamatown_EventScript_Tangela_Text_2:
# 98 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.$"

Tamatown_EventScript_Tangela_Text_3:
# 102 "data/maps/Tamatown/scripts.pory"
	.string "Yep$"

Tamatown_EventScript_Tangela_Text_4:
# 103 "data/maps/Tamatown/scripts.pory"
	.string "Totes$"

Tamatown_EventScript_Tangela_Text_5:
# 117 "data/maps/Tamatown/scripts.pory"
	.string "The tree moved impatiently.$"

Tamatown_EventScript_Tangela_Text_6:
# 121 "data/maps/Tamatown/scripts.pory"
	.string "Hmm.$"

Tamatown_EventScript_Tangela_Text_7:
# 122 "data/maps/Tamatown/scripts.pory"
	.string "Ahem.$"

Tamatown_EventScript_Tangela_Text_8:
# 135 "data/maps/Tamatown/scripts.pory"
	.string "Tree$"

Tamatown_EventScript_Tangela_Text_9:
# 137 "data/maps/Tamatown/scripts.pory"
	.string "{FONT_SMALL}Hee hee hee hee…{FONT_NORMAL}$"

Tamatown_EventScript_Tangela_Text_10:
# 141 "data/maps/Tamatown/scripts.pory"
	.string "Were you hiding?$"

Tamatown_EventScript_Tangela_Text_11:
# 142 "data/maps/Tamatown/scripts.pory"
	.string "I can see you$"

Tamatown_EventScript_Tangela_Text_12:
# 153 "data/maps/Tamatown/scripts.pory"
	.string "What? Oh, man!\p"
	.string "I was trying out my new “hiding in\nplain sight” secret technique…\l"
	.string "But you saw right through me!\p"
	.string "You must be some kind of genius!$"

Tamatown_EventScript_Sign_Text_0:
# 171 "data/maps/Tamatown/scripts.pory"
	.string "“6 Week Course: How To Manipulate\nYour Human Through Pooping”$"

Tamatown_EventScript_Trashcan_Text_0:
# 181 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "As hungry as it makes you, you need\nto go.$"

Tamatown_EventScript_TrubbishCan_Text_0:
# 191 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "…Wait a second…\nDid the trashcan just move?$"

Tamatown_EventScript_TrubbishCan_Text_1:
# 196 "data/maps/Tamatown/scripts.pory"
	.string "It did!$"

Tamatown_EventScript_TrubbishCan_Text_2:
# 197 "data/maps/Tamatown/scripts.pory"
	.string "I'm imagining things.$"

Tamatown_EventScript_TrubbishCan_Text_3:
# 202 "data/maps/Tamatown/scripts.pory"
	.string "What to do?$"

Tamatown_EventScript_TrubbishCan_Text_4:
# 206 "data/maps/Tamatown/scripts.pory"
	.string "Kick it.$"

Tamatown_EventScript_TrubbishCan_Text_5:
# 207 "data/maps/Tamatown/scripts.pory"
	.string "Hug it.$"

Tamatown_EventScript_TrubbishCan_Text_6:
# 217 "data/maps/Tamatown/scripts.pory"
	.string "Trashcan?$"

Tamatown_EventScript_TrubbishCan_Text_7:
# 219 "data/maps/Tamatown/scripts.pory"
	.string "WAIT! WAIT! STOP!$"

Tamatown_EventScript_TrubbishCan_Text_8:
# 237 "data/maps/Tamatown/scripts.pory"
	.string "Trubbish$"

Tamatown_EventScript_TrubbishCan_Text_9:
# 239 "data/maps/Tamatown/scripts.pory"
	.string "Whew! You almost got me there!\nNo, I wasn't hiding…\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_10:
# 253 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks… happy?$"

Tamatown_EventScript_TrubbishCan_Text_11:
# 266 "data/maps/Tamatown/scripts.pory"
	.string "I-I've never been held with such\nkindness before…\p"
	.string "Thanks, buddy.\nI'm happy you don't think I'm trash!\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_12:
# 279 "data/maps/Tamatown/scripts.pory"
	.string "You got the Doughnut!$"

Tamatown_EventScript_TrubbishCan_Text_13:
# 286 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks saddened.$"

Tamatown_EventScript_Slowpoke_Text_0:
# 298 "data/maps/Tamatown/scripts.pory"
	.string "Slowpoke$"

Tamatown_EventScript_Slowpoke_Text_1:
# 300 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "… … … … … … …\p"
	.string "We opened up our restaurant\nreeeeecently… Buuuut…\p"
	.string "Customers don't tiiiiiiiip…\p"
	.string "They say the service is too sloooow…\p"
	.string "Can you belieeeeve it?\p"
	.string "You look faaaaast enouuuuuugh…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_2:
# 311 "data/maps/Tamatown/scripts.pory"
	.string "For sure!$"

Tamatown_EventScript_Slowpoke_Text_3:
# 312 "data/maps/Tamatown/scripts.pory"
	.string "Sounds tiring…$"

Tamatown_EventScript_Slowpoke_Text_4:
# 319 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Yaaaaaaaaaaaaaaaaaaay…$"

Tamatown_EventScript_Slowpoke_Text_5:
# 327 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "I understaaaand…\p"
	.string "It's suuuuuper tiiiiiiring…$"
