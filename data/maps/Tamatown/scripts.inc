Tamatown_MapScripts::
	.byte 0


Tamatown_EventScript_Porygon::
# 9 "data/maps/Tamatown/scripts.pory"
	lock
# 11 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_0, MSGBOX_YESNO
# 16 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 17 "data/maps/Tamatown/scripts.pory"
	case YES, Tamatown_EventScript_Porygon_3
# 24 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_2, MSGBOX_YESNO
Tamatown_EventScript_Porygon_1:
# 30 "data/maps/Tamatown/scripts.pory"
	closemessage
# 32 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Porygon_3:
# 18 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_1, MSGBOX_YESNO
	goto Tamatown_EventScript_Porygon_1


Tamatown_EventScript_Tree::
# 36 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tree_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_Tangela::
# 43 "data/maps/Tamatown/scripts.pory"
	lock
# 45 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_FOUND_TANGELA, Tamatown_EventScript_Tangela_2
# 53 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_2
# 57 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_3, Tamatown_EventScript_Tangela_Text_4
# 62 "data/maps/Tamatown/scripts.pory"
	closemessage
# 64 "data/maps/Tamatown/scripts.pory"
	delay 24
# 67 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 69 "data/maps/Tamatown/scripts.pory"
	waitse
# 72 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_5
# 76 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_6, Tamatown_EventScript_Tangela_Text_7
# 81 "data/maps/Tamatown/scripts.pory"
	closemessage
# 83 "data/maps/Tamatown/scripts.pory"
	delay 24
# 86 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 88 "data/maps/Tamatown/scripts.pory"
	waitse
# 91 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_8
# 92 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_9
# 96 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_10, Tamatown_EventScript_Tangela_Text_11
# 101 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 102 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_0
# 103 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 104 "data/maps/Tamatown/scripts.pory"
	waitse
# 106 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 107 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 108 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_12
# 114 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 116 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_FOUND_TANGELA
Tamatown_EventScript_Tangela_1:
# 119 "data/maps/Tamatown/scripts.pory"
	closemessage
# 121 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Tangela_2:
# 46 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 47 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 48 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_1
# 51 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Tangela_1


Tamatown_EventScript_Sign::
# 125 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Sign_Text_0, MSGBOX_SIGN
	return


Tamatown_EventScript_Skitty::
	return


Tamatown_EventScript_Trashcan::
# 136 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Trashcan_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_TrubbishCan::
# 144 "data/maps/Tamatown/scripts.pory"
	lock
# 146 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_0
# 151 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TrubbishCan_Text_1, Tamatown_EventScript_TrubbishCan_Text_2
# 156 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_2
# 241 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_13
Tamatown_EventScript_TrubbishCan_1:
# 245 "data/maps/Tamatown/scripts.pory"
	closemessage
# 247 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TrubbishCan_2:
# 157 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_3
# 161 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_TrubbishCan_Text_4, Tamatown_EventScript_TrubbishCan_Text_5
# 166 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_6
# 203 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 204 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_TrubbishCan_Movement_1
# 205 "data/maps/Tamatown/scripts.pory"
	waitse
# 206 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 208 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_10
# 211 "data/maps/Tamatown/scripts.pory"
	closemessage
# 213 "data/maps/Tamatown/scripts.pory"
	clearflag FLAG_HIDE_TRUBBISH
# 214 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 216 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 217 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 218 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 220 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_8
# 221 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_11
Tamatown_EventScript_TrubbishCan_5:
# 230 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_UNLOCKED_SNACK_DOUGHNUT
# 232 "data/maps/Tamatown/scripts.pory"
	setspeaker NULL
# 233 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 234 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_12
# 237 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 238 "data/maps/Tamatown/scripts.pory"
	closemessage
# 239 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_TEMP_1
	goto Tamatown_EventScript_TrubbishCan_1

Tamatown_EventScript_TrubbishCan_6:
# 167 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 0
# 168 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 3
# 169 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 4
# 170 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 171 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 172 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 173 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_6
# 174 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_7
# 178 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 179 "data/maps/Tamatown/scripts.pory"
	closemessage
# 181 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 182 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_0
# 183 "data/maps/Tamatown/scripts.pory"
	waitse
# 184 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 186 "data/maps/Tamatown/scripts.pory"
	clearflag FLAG_HIDE_TRUBBISH
# 187 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 189 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 190 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 191 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 193 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_8
# 194 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_9
	goto Tamatown_EventScript_TrubbishCan_5


Tamatown_EventScript_Slowpoke::
# 251 "data/maps/Tamatown/scripts.pory"
	lock
# 253 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 254 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 255 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_1
# 266 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Slowpoke_Text_2, Tamatown_EventScript_Slowpoke_Text_3
# 271 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Slowpoke_2
# 280 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_FAINT
# 281 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 282 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_5
Tamatown_EventScript_Slowpoke_1:
# 289 "data/maps/Tamatown/scripts.pory"
	closemessage
# 291 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Slowpoke_2:
# 272 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 273 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 274 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_4
	goto Tamatown_EventScript_Slowpoke_1


# 102 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_0:
# 102 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
# 102 "data/maps/Tamatown/scripts.pory"
	delay_16
# 102 "data/maps/Tamatown/scripts.pory"
	delay_16
# 102 "data/maps/Tamatown/scripts.pory"
	delay_16
# 102 "data/maps/Tamatown/scripts.pory"
	delay_16
# 102 "data/maps/Tamatown/scripts.pory"
	delay_16
# 102 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 190 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_0:
# 190 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 190 "data/maps/Tamatown/scripts.pory"
	delay_16
# 190 "data/maps/Tamatown/scripts.pory"
	delay_16
# 190 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 204 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_1:
# 204 "data/maps/Tamatown/scripts.pory"
	emote_heart
# 204 "data/maps/Tamatown/scripts.pory"
	delay_16
# 204 "data/maps/Tamatown/scripts.pory"
	delay_16
# 204 "data/maps/Tamatown/scripts.pory"
	delay_16
# 204 "data/maps/Tamatown/scripts.pory"
	delay_16
# 204 "data/maps/Tamatown/scripts.pory"
	delay_16
# 204 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

Tamatown_EventScript_Porygon_Text_0:
# 12 "data/maps/Tamatown/scripts.pory"
	.string "Yo, my man, wanna try beating my high score?$"

Tamatown_EventScript_Porygon_Text_1:
# 19 "data/maps/Tamatown/scripts.pory"
	.string "Heck yeah!$"

Tamatown_EventScript_Porygon_Text_2:
# 25 "data/maps/Tamatown/scripts.pory"
	.string "Aight, aight, guess I'll remain…\nUNBEATEN!!!$"

Tamatown_EventScript_Tree_Text_0:
# 37 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.\nIt kinda looks like your cousin Mark.$"

Tamatown_EventScript_Tangela_Text_0:
# 47 "data/maps/Tamatown/scripts.pory"
	.string "Tangela$"

Tamatown_EventScript_Tangela_Text_1:
# 49 "data/maps/Tamatown/scripts.pory"
	.string "Don't look at me!\nI am invisible!$"

Tamatown_EventScript_Tangela_Text_2:
# 54 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.$"

Tamatown_EventScript_Tangela_Text_3:
# 58 "data/maps/Tamatown/scripts.pory"
	.string "Yep$"

Tamatown_EventScript_Tangela_Text_4:
# 59 "data/maps/Tamatown/scripts.pory"
	.string "Totes$"

Tamatown_EventScript_Tangela_Text_5:
# 73 "data/maps/Tamatown/scripts.pory"
	.string "The tree moved impatiently.$"

Tamatown_EventScript_Tangela_Text_6:
# 77 "data/maps/Tamatown/scripts.pory"
	.string "Hmm.$"

Tamatown_EventScript_Tangela_Text_7:
# 78 "data/maps/Tamatown/scripts.pory"
	.string "Ahem.$"

Tamatown_EventScript_Tangela_Text_8:
# 91 "data/maps/Tamatown/scripts.pory"
	.string "Tree$"

Tamatown_EventScript_Tangela_Text_9:
# 93 "data/maps/Tamatown/scripts.pory"
	.string "{FONT_SMALL}Hee hee hee hee…{FONT_NORMAL}$"

Tamatown_EventScript_Tangela_Text_10:
# 97 "data/maps/Tamatown/scripts.pory"
	.string "Were you hiding?$"

Tamatown_EventScript_Tangela_Text_11:
# 98 "data/maps/Tamatown/scripts.pory"
	.string "I can see you$"

Tamatown_EventScript_Tangela_Text_12:
# 109 "data/maps/Tamatown/scripts.pory"
	.string "What? Oh, man!\p"
	.string "I was trying out my new “hiding in\nplain sight” secret technique…\l"
	.string "But you saw right through me!\p"
	.string "You must be some kind of genius!$"

Tamatown_EventScript_Sign_Text_0:
# 127 "data/maps/Tamatown/scripts.pory"
	.string "“6 Week Course: How To Manipulate\nYour Human Through Pooping”$"

Tamatown_EventScript_Trashcan_Text_0:
# 137 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "As hungry as it makes you, you need\nto go.$"

Tamatown_EventScript_TrubbishCan_Text_0:
# 147 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "…Wait a second…\nDid the trashcan just move?$"

Tamatown_EventScript_TrubbishCan_Text_1:
# 152 "data/maps/Tamatown/scripts.pory"
	.string "It did!$"

Tamatown_EventScript_TrubbishCan_Text_2:
# 153 "data/maps/Tamatown/scripts.pory"
	.string "I'm imagining things.$"

Tamatown_EventScript_TrubbishCan_Text_3:
# 158 "data/maps/Tamatown/scripts.pory"
	.string "What to do?$"

Tamatown_EventScript_TrubbishCan_Text_4:
# 162 "data/maps/Tamatown/scripts.pory"
	.string "Kick it.$"

Tamatown_EventScript_TrubbishCan_Text_5:
# 163 "data/maps/Tamatown/scripts.pory"
	.string "Hug it.$"

Tamatown_EventScript_TrubbishCan_Text_6:
# 173 "data/maps/Tamatown/scripts.pory"
	.string "Trashcan?$"

Tamatown_EventScript_TrubbishCan_Text_7:
# 175 "data/maps/Tamatown/scripts.pory"
	.string "WAIT! WAIT! STOP!$"

Tamatown_EventScript_TrubbishCan_Text_8:
# 193 "data/maps/Tamatown/scripts.pory"
	.string "Trubbish$"

Tamatown_EventScript_TrubbishCan_Text_9:
# 195 "data/maps/Tamatown/scripts.pory"
	.string "Whew! You almost got me there!\nNo, I wasn't hiding…\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_10:
# 209 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks… happy?$"

Tamatown_EventScript_TrubbishCan_Text_11:
# 222 "data/maps/Tamatown/scripts.pory"
	.string "I-I've never been held with such\nkindness before…\p"
	.string "Thanks, buddy.\nI'm happy you don't think I'm trash!\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_12:
# 235 "data/maps/Tamatown/scripts.pory"
	.string "You got the Doughnut!$"

Tamatown_EventScript_TrubbishCan_Text_13:
# 242 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks saddened.$"

Tamatown_EventScript_Slowpoke_Text_0:
# 254 "data/maps/Tamatown/scripts.pory"
	.string "Slowpoke$"

Tamatown_EventScript_Slowpoke_Text_1:
# 256 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "… … … … … … …\p"
	.string "We opened up our restaurant\nreeeeecently… Buuuut…\p"
	.string "Customers don't tiiiiiiiip…\p"
	.string "They say the service is too sloooow…\p"
	.string "Can you belieeeeve it?\p"
	.string "You look faaaaast enouuuuuugh…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_2:
# 267 "data/maps/Tamatown/scripts.pory"
	.string "For sure!$"

Tamatown_EventScript_Slowpoke_Text_3:
# 268 "data/maps/Tamatown/scripts.pory"
	.string "Sounds tiring…$"

Tamatown_EventScript_Slowpoke_Text_4:
# 275 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Yaaaaaaaaaaaaaaaaaaay…$"

Tamatown_EventScript_Slowpoke_Text_5:
# 283 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "I understaaaand…\p"
	.string "It's suuuuuper tiiiiiiring…$"
