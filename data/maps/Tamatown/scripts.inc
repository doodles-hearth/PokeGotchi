Tamatown_MapScripts::
	.byte 0


Tamatown_EventScript_Porygon::
# 9 "data/maps/Tamatown/scripts.pory"
	lockall
# 11 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_0
# 18 "data/maps/Tamatown/scripts.pory"
	closemessage
# 20 "data/maps/Tamatown/scripts.pory"
	goto_if_unset FLAG_RECEIVED_PACHINKO_COINS, Tamatown_EventScript_Porygon_2
Tamatown_EventScript_Porygon_1:
# 34 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Porygon_Text_2, Tamatown_EventScript_Porygon_Text_3
# 39 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 40 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_Porygon_6
# 64 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_5, MSGBOX_YESNO
# 70 "data/maps/Tamatown/scripts.pory"
	closemessage
# 72 "data/maps/Tamatown/scripts.pory"
	releaseall
	return

Tamatown_EventScript_Porygon_2:
# 21 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Porygon_Text_1
# 24 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 25 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 27 "data/maps/Tamatown/scripts.pory"
	addcoins 15
# 29 "data/maps/Tamatown/scripts.pory"
	closemessage
# 31 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_PACHINKO_COINS
	goto Tamatown_EventScript_Porygon_1

Tamatown_EventScript_Porygon_6:
# 41 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_4
# 44 "data/maps/Tamatown/scripts.pory"
	closemessage
# 46 "data/maps/Tamatown/scripts.pory"
	switch VAR_FACING
# 47 "data/maps/Tamatown/scripts.pory"
	case DIR_NORTH, Tamatown_EventScript_Porygon_10
# 49 "data/maps/Tamatown/scripts.pory"
	case DIR_SOUTH, Tamatown_EventScript_Porygon_11
# 51 "data/maps/Tamatown/scripts.pory"
	case DIR_EAST, Tamatown_EventScript_Porygon_12
Tamatown_EventScript_Porygon_8:
# 55 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 56 "data/maps/Tamatown/scripts.pory"
	delay 32
# 57 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 58 "data/maps/Tamatown/scripts.pory"
	waitstate
# 59 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 60 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 61 "data/maps/Tamatown/scripts.pory"
	releaseall
	end

Tamatown_EventScript_Porygon_10:
# 48 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_0
	goto Tamatown_EventScript_Porygon_8

Tamatown_EventScript_Porygon_11:
# 50 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_1
	goto Tamatown_EventScript_Porygon_8

Tamatown_EventScript_Porygon_12:
# 52 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_2
	goto Tamatown_EventScript_Porygon_8


Tamatown_EventScript_Tree::
# 76 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tree_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_Tangela::
# 83 "data/maps/Tamatown/scripts.pory"
	lock
# 85 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FOUND_TANGELA, Tamatown_EventScript_Tangela_2
# 93 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_2
# 97 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_3, Tamatown_EventScript_Tangela_Text_4
# 102 "data/maps/Tamatown/scripts.pory"
	closemessage
# 104 "data/maps/Tamatown/scripts.pory"
	delay 24
# 107 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 109 "data/maps/Tamatown/scripts.pory"
	waitse
# 112 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_5
# 116 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_6, Tamatown_EventScript_Tangela_Text_7
# 121 "data/maps/Tamatown/scripts.pory"
	closemessage
# 123 "data/maps/Tamatown/scripts.pory"
	delay 24
# 126 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 128 "data/maps/Tamatown/scripts.pory"
	waitse
# 131 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_8
# 132 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_9
# 136 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_10, Tamatown_EventScript_Tangela_Text_11
# 141 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 142 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_0
# 143 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 144 "data/maps/Tamatown/scripts.pory"
	waitse
# 146 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 147 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 148 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_12
# 154 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 156 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FOUND_TANGELA
Tamatown_EventScript_Tangela_1:
# 159 "data/maps/Tamatown/scripts.pory"
	closemessage
# 161 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Tangela_2:
# 86 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 87 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 88 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_1
# 91 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Tangela_1


Tamatown_EventScript_Sign::
# 165 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Sign_Text_0, MSGBOX_SIGN
	return


Tamatown_EventScript_Skitty::
	return


Tamatown_EventScript_Trashcan::
# 176 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Trashcan_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_TrubbishCan::
# 184 "data/maps/Tamatown/scripts.pory"
	lock
# 186 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_0
# 191 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TrubbishCan_Text_1, Tamatown_EventScript_TrubbishCan_Text_2
# 196 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_2
# 281 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_13
Tamatown_EventScript_TrubbishCan_1:
# 285 "data/maps/Tamatown/scripts.pory"
	closemessage
# 287 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TrubbishCan_2:
# 197 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_3
# 201 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_TrubbishCan_Text_4, Tamatown_EventScript_TrubbishCan_Text_5
# 206 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_6
# 243 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 244 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_TrubbishCan_Movement_1
# 245 "data/maps/Tamatown/scripts.pory"
	waitse
# 246 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 248 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_10
# 251 "data/maps/Tamatown/scripts.pory"
	closemessage
# 253 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 254 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 256 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 257 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 258 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 260 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_8
# 261 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_11
Tamatown_EventScript_TrubbishCan_5:
# 270 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT
# 272 "data/maps/Tamatown/scripts.pory"
	setspeaker NULL
# 273 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 274 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_12
# 277 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 278 "data/maps/Tamatown/scripts.pory"
	closemessage
# 279 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_TEMP_1
	goto Tamatown_EventScript_TrubbishCan_1

Tamatown_EventScript_TrubbishCan_6:
# 207 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 0
# 208 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 3
# 209 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 4
# 210 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 211 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 212 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 213 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_6
# 214 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_7
# 218 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 219 "data/maps/Tamatown/scripts.pory"
	closemessage
# 221 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 222 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_0
# 223 "data/maps/Tamatown/scripts.pory"
	waitse
# 224 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 226 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 227 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 229 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 230 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 231 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 233 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_8
# 234 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_9
	goto Tamatown_EventScript_TrubbishCan_5


Tamatown_EventScript_Slowpoke::
# 291 "data/maps/Tamatown/scripts.pory"
	lock
# 293 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 294 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 295 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_1
# 306 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Slowpoke_Text_2, Tamatown_EventScript_Slowpoke_Text_3
# 311 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Slowpoke_2
# 320 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_FAINT
# 321 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 322 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_5
Tamatown_EventScript_Slowpoke_1:
# 329 "data/maps/Tamatown/scripts.pory"
	closemessage
# 331 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Slowpoke_2:
# 312 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 313 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 314 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_4
	goto Tamatown_EventScript_Slowpoke_1


# 48 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_0:
# 48 "data/maps/Tamatown/scripts.pory"
	walk_right
# 48 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 50 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_1:
# 50 "data/maps/Tamatown/scripts.pory"
	walk_left
# 50 "data/maps/Tamatown/scripts.pory"
	walk_down
# 50 "data/maps/Tamatown/scripts.pory"
	walk_down
# 50 "data/maps/Tamatown/scripts.pory"
	walk_right
# 50 "data/maps/Tamatown/scripts.pory"
	walk_right
# 50 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 52 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_2:
# 52 "data/maps/Tamatown/scripts.pory"
	walk_down
# 52 "data/maps/Tamatown/scripts.pory"
	walk_right
# 52 "data/maps/Tamatown/scripts.pory"
	walk_right
# 52 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 142 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_0:
# 142 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
# 142 "data/maps/Tamatown/scripts.pory"
	delay_16
# 142 "data/maps/Tamatown/scripts.pory"
	delay_16
# 142 "data/maps/Tamatown/scripts.pory"
	delay_16
# 142 "data/maps/Tamatown/scripts.pory"
	delay_16
# 142 "data/maps/Tamatown/scripts.pory"
	delay_16
# 142 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 230 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_0:
# 230 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 230 "data/maps/Tamatown/scripts.pory"
	delay_16
# 230 "data/maps/Tamatown/scripts.pory"
	delay_16
# 230 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 244 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_1:
# 244 "data/maps/Tamatown/scripts.pory"
	emote_heart
# 244 "data/maps/Tamatown/scripts.pory"
	delay_16
# 244 "data/maps/Tamatown/scripts.pory"
	delay_16
# 244 "data/maps/Tamatown/scripts.pory"
	delay_16
# 244 "data/maps/Tamatown/scripts.pory"
	delay_16
# 244 "data/maps/Tamatown/scripts.pory"
	delay_16
# 244 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

Tamatown_EventScript_Porygon_Text_0:
# 12 "data/maps/Tamatown/scripts.pory"
	.string "Yo, my man, come over here…\p"
	.string "Wanna try your luck at the most fun\nway to lose money ever invented?\l"
	.string "That's right, PACHINKO!!\p"
	.string "A game costs 3 coins.\nI'll give you 15 coins everyday!\p"
	.string "What are the coins for? Uhh…\nThey look super neat!$"

Tamatown_EventScript_Porygon_Text_1:
# 22 "data/maps/Tamatown/scripts.pory"
	.string "You got 15 coins!$"

Tamatown_EventScript_Porygon_Text_2:
# 35 "data/maps/Tamatown/scripts.pory"
	.string "I wanna play!$"

Tamatown_EventScript_Porygon_Text_3:
# 36 "data/maps/Tamatown/scripts.pory"
	.string "Nah.$"

Tamatown_EventScript_Porygon_Text_4:
# 42 "data/maps/Tamatown/scripts.pory"
	.string "Heck yeah! Have fun!$"

Tamatown_EventScript_Porygon_Text_5:
# 65 "data/maps/Tamatown/scripts.pory"
	.string "Aight, aight, can't help ya if you\nhate fun…$"

Tamatown_EventScript_Tree_Text_0:
# 77 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.\nIt kinda looks like your cousin Mark.$"

Tamatown_EventScript_Tangela_Text_0:
# 87 "data/maps/Tamatown/scripts.pory"
	.string "Tangela$"

Tamatown_EventScript_Tangela_Text_1:
# 89 "data/maps/Tamatown/scripts.pory"
	.string "Don't look at me!\nI am invisible!$"

Tamatown_EventScript_Tangela_Text_2:
# 94 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.$"

Tamatown_EventScript_Tangela_Text_3:
# 98 "data/maps/Tamatown/scripts.pory"
	.string "Yep$"

Tamatown_EventScript_Tangela_Text_4:
# 99 "data/maps/Tamatown/scripts.pory"
	.string "Totes$"

Tamatown_EventScript_Tangela_Text_5:
# 113 "data/maps/Tamatown/scripts.pory"
	.string "The tree moved impatiently.$"

Tamatown_EventScript_Tangela_Text_6:
# 117 "data/maps/Tamatown/scripts.pory"
	.string "Hmm.$"

Tamatown_EventScript_Tangela_Text_7:
# 118 "data/maps/Tamatown/scripts.pory"
	.string "Ahem.$"

Tamatown_EventScript_Tangela_Text_8:
# 131 "data/maps/Tamatown/scripts.pory"
	.string "Tree$"

Tamatown_EventScript_Tangela_Text_9:
# 133 "data/maps/Tamatown/scripts.pory"
	.string "{FONT_SMALL}Hee hee hee hee…{FONT_NORMAL}$"

Tamatown_EventScript_Tangela_Text_10:
# 137 "data/maps/Tamatown/scripts.pory"
	.string "Were you hiding?$"

Tamatown_EventScript_Tangela_Text_11:
# 138 "data/maps/Tamatown/scripts.pory"
	.string "I can see you$"

Tamatown_EventScript_Tangela_Text_12:
# 149 "data/maps/Tamatown/scripts.pory"
	.string "What? Oh, man!\p"
	.string "I was trying out my new “hiding in\nplain sight” secret technique…\l"
	.string "But you saw right through me!\p"
	.string "You must be some kind of genius!$"

Tamatown_EventScript_Sign_Text_0:
# 167 "data/maps/Tamatown/scripts.pory"
	.string "“6 Week Course: How To Manipulate\nYour Human Through Pooping”$"

Tamatown_EventScript_Trashcan_Text_0:
# 177 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "As hungry as it makes you, you need\nto go.$"

Tamatown_EventScript_TrubbishCan_Text_0:
# 187 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "…Wait a second…\nDid the trashcan just move?$"

Tamatown_EventScript_TrubbishCan_Text_1:
# 192 "data/maps/Tamatown/scripts.pory"
	.string "It did!$"

Tamatown_EventScript_TrubbishCan_Text_2:
# 193 "data/maps/Tamatown/scripts.pory"
	.string "I'm imagining things.$"

Tamatown_EventScript_TrubbishCan_Text_3:
# 198 "data/maps/Tamatown/scripts.pory"
	.string "What to do?$"

Tamatown_EventScript_TrubbishCan_Text_4:
# 202 "data/maps/Tamatown/scripts.pory"
	.string "Kick it.$"

Tamatown_EventScript_TrubbishCan_Text_5:
# 203 "data/maps/Tamatown/scripts.pory"
	.string "Hug it.$"

Tamatown_EventScript_TrubbishCan_Text_6:
# 213 "data/maps/Tamatown/scripts.pory"
	.string "Trashcan?$"

Tamatown_EventScript_TrubbishCan_Text_7:
# 215 "data/maps/Tamatown/scripts.pory"
	.string "WAIT! WAIT! STOP!$"

Tamatown_EventScript_TrubbishCan_Text_8:
# 233 "data/maps/Tamatown/scripts.pory"
	.string "Trubbish$"

Tamatown_EventScript_TrubbishCan_Text_9:
# 235 "data/maps/Tamatown/scripts.pory"
	.string "Whew! You almost got me there!\nNo, I wasn't hiding…\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_10:
# 249 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks… happy?$"

Tamatown_EventScript_TrubbishCan_Text_11:
# 262 "data/maps/Tamatown/scripts.pory"
	.string "I-I've never been held with such\nkindness before…\p"
	.string "Thanks, buddy.\nI'm happy you don't think I'm trash!\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_12:
# 275 "data/maps/Tamatown/scripts.pory"
	.string "You got the Doughnut!$"

Tamatown_EventScript_TrubbishCan_Text_13:
# 282 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks saddened.$"

Tamatown_EventScript_Slowpoke_Text_0:
# 294 "data/maps/Tamatown/scripts.pory"
	.string "Slowpoke$"

Tamatown_EventScript_Slowpoke_Text_1:
# 296 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "… … … … … … …\p"
	.string "We opened up our restaurant\nreeeeecently… Buuuut…\p"
	.string "Customers don't tiiiiiiiip…\p"
	.string "They say the service is too sloooow…\p"
	.string "Can you belieeeeve it?\p"
	.string "You look faaaaast enouuuuuugh…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_2:
# 307 "data/maps/Tamatown/scripts.pory"
	.string "For sure!$"

Tamatown_EventScript_Slowpoke_Text_3:
# 308 "data/maps/Tamatown/scripts.pory"
	.string "Sounds tiring…$"

Tamatown_EventScript_Slowpoke_Text_4:
# 315 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Yaaaaaaaaaaaaaaaaaaay…$"

Tamatown_EventScript_Slowpoke_Text_5:
# 323 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "I understaaaand…\p"
	.string "It's suuuuuper tiiiiiiring…$"
