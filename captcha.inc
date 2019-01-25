/*

		Captcha для SAMP сервера.
		Автор: Nestyreff

		Условия использования: свободный доступ.
		Условия редактирования и репостинга: с разрешения автора.

*/

#define CAPTCHA_DIALOG
#define CAPTCHA_ERROR

#if !defined CAPTCHA_WithoutConfig // проверяем наличие настройки "Без настроек"
	#if !defined ini_Open // проверяем наличие mxINI
		#tryinclude <mxINI.inc> // пытаемся подключить mxINI
		#if !defined ini_Open // если после попытки не подключен, то идем дальше
			#error "Please include mxINI for configuration or put in your gamemode #define CAPTCHA_WithoutConfig"
		#else
			new captcha_file;
			new captcha_exec;
		#endif
	#endif
#endif

new static const captcha_colors [5] [8] =
{
	"0x00FF00", // Зеленый
	"0xFF0000", // Синий
	"0xFF8000", // Голубой
	"0x0000FF", // Красный
	"0x00FFFF" // Желтый
};

#if !defined CAPTCHA_Lang_Included

// LANG Text

#define CAPTCHA_APPLY 	"Далее"
#define CAPTCHA_CAPTION "Капча"
#define CAPTCHA_ERROR	"Ошибка. \nПопробуйте еще раз."
#define CAPTCHA_INFO 	"Введите ответ на вопрос,\nНе используйте посторонних символов\nЧетко и правильно дайте ответ на вопрос. Пример : G1 \n%s"
#define CAPTCHA_BANNED 	"Вы были заблокированы на данном сервере ввиду использования постороннего софта (Автоматизация действий)"
#define CAPTCHA_KICKED 	"Вы были отключены по подозрению в использовании постороннего софта (Автоматизация действий)"


new const captcha_Questions [17]
{
	"Сколько углов имеет фигура G1?",
	"Сколько углов имеет фигура G4?",
	"Сколько углов имеет фигура G3?",
	"Сколько углов имеет фигура G0?",
	"Какая фигура выходит за грани экрана?",
	"Какая фигура самая большая?",
	"Какая фигура в форме пьедестала (место, где стоят победители при награждении)?",
	"Какая фигура самая маленькая?",
	"Какая фигура имеет форму зиг-зага?",
	"Какая фигура имеет форму горизонтального прямоугольника?",
	"Какая фигура имеет форму вертикального прямоугольника?",
	"На какой фигуре больше всего надписей?",
	"На каких фигурах по 2 надписи?",
	"На какой фиуре текст выходит из рамок?",
	"Какая фигура красная?",
	"Текст какой фигуры находится левее всех?"
};

new captcha_Answers [17]
{
	"8",
	"8",
	"2",
	"4",
	"G3",
	"G3",
	"G1",
	"G2",
	"G4",
	"G0",
	"G5",
	"G1",
	"G5, G6",
	"G2",
	"",
	"G2"
}

#endif

new Text:captcha_Txt [MAX_PLAYERS] [10];


#if !defined CAPTCHA_DIFFICULTY
	#define CAPCTHA_DIFFICULTY  1 // Можно изменить на свое в моде 1 - стандарт
#endif


forward GenerateCaptchaDialog (playerid), public GenerateCaptchaDialog(playerid)
{

	SetPVarInt(playerid, "Captcha_Quest", random(sizeof(captcha_Questions))); // Генерируем вопрос и сразу записываем в Captcha_Quest

	new captcha_tmp_string [128], question = GetPVarInt(playerid, "Captcha_Quest"); 
	format( captcha_tmp_string, sizeof(captcha_tmp_string), CAPTCHA_INFO, captcha_Answers [question]] ); // формируем текст вопроса
	ShowPlayerDialog(playerid, CAPTCHA_DIALOG, DIALOG_STYLE_INPUT, CAPTCHA_CAPTION, captcha_tmp_string, CAPTCHA_APPLY, ""); // показываем диалог

	new 
		idx = random(sizeof(captcha_colors)), color [8] = captcha_colors [idx],
		prop = random(1);

	captcha_txt [playerid] [0] = TextDrawCreate(456.000000, 342.000000, "G1");
	TextDrawAlignment(captcha_txt [playerid] [0], 2);
	TextDrawBackgroundColor(captcha_txt [playerid] [0], -1);
	TextDrawFont(captcha_txt [playerid] [0], 1);
	TextDrawLetterSize(captcha_txt [playerid] [0], 0.500000, 1.300000);
	TextDrawColor(captcha_txt [playerid] [0], color);
	TextDrawSetOutline(captcha_txt [playerid] [0], 1);
	TextDrawSetProportional(captcha_txt [playerid] [0], prop);
	TextDrawUseBox(captcha_txt [playerid] [0], 1);
	TextDrawBoxColor(captcha_txt [playerid] [0], 255);
	TextDrawTextSize(captcha_txt [playerid] [0], 209.000000, -130.000000);

	captcha_txt [playerid] [1] = TextDrawCreate(456.000000, 329.000000, "G1");
	TextDrawAlignment(captcha_txt [playerid] [1], 2);
	TextDrawBackgroundColor(captcha_txt [playerid] [1], -1);
	TextDrawFont(captcha_txt [playerid] [1], 1);
	TextDrawLetterSize(captcha_txt [playerid] [1], 0.579999, 1.000000);
	TextDrawColor(captcha_txt [playerid] [1], color);
	TextDrawSetOutline(captcha_txt [playerid] [1], 1);
	TextDrawSetProportional(captcha_txt [playerid] [1], prop);
	TextDrawUseBox(captcha_txt [playerid] [1], 1);
	TextDrawBoxColor(captcha_txt [playerid] [1], 255);
	TextDrawTextSize(captcha_txt [playerid] [1], 167.000000, -50.000000);

	captcha_txt [playerid] [2] = TextDrawCreate(456.000000, 316.000000, "G1");
	TextDrawAlignment(captcha_txt [playerid] [2], 2);
	TextDrawBackgroundColor(captcha_txt [playerid] [2], -1);
	TextDrawFont(captcha_txt [playerid] [2], 1);
	TextDrawLetterSize(captcha_txt [playerid] [2], 0.430000, 1.000000);
	TextDrawColor(captcha_txt [playerid] [2], color);
	TextDrawSetOutline(captcha_txt [playerid] [2], 1);
	TextDrawSetProportional(captcha_txt [playerid] [2], prop);
	TextDrawUseBox(captcha_txt [playerid] [2], 1);
	TextDrawBoxColor(captcha_txt [playerid] [2], 255);
	TextDrawTextSize(captcha_txt [playerid] [2], 167.000000, -50.000000);

	captcha_txt [playerid] [3] = TextDrawCreate(416.000000, 245.000000, "G2");
	TextDrawAlignment(captcha_txt [playerid] [3], 2);
	TextDrawBackgroundColor(captcha_txt [playerid] [3], -1);
	TextDrawFont(captcha_txt [playerid] [3], 1);
	TextDrawLetterSize(captcha_txt [playerid] [3], 1.059999, 4.000000);
	TextDrawColor(captcha_txt [playerid] [3], color);
	TextDrawSetOutline(captcha_txt [playerid] [3], 1);
	TextDrawSetProportional(captcha_txt [playerid] [0], prop);
	TextDrawUseBox(captcha_txt [playerid] [3], 1);
	TextDrawBoxColor(captcha_txt [playerid] [3], 255);
	TextDrawTextSize(captcha_txt [playerid] [3], 200.000000, -21.000000);

	captcha_txt [playerid] [4] = TextDrawCreate(379.000000, 295.000000, "G0");
	TextDrawAlignment(captcha_txt [playerid] [4], 2);
	TextDrawBackgroundColor(captcha_txt [playerid] [4], -1);
	TextDrawFont(captcha_txt [playerid] [4], 1);
	TextDrawLetterSize(captcha_txt [playerid] [4], 0.859999, 2.899999);
	TextDrawColor(captcha_txt [playerid] [4], color);
	TextDrawSetOutline(captcha_txt [playerid] [4], 1);
	TextDrawSetProportional(captcha_txt [playerid] [0], prop);
	TextDrawUseBox(captcha_txt [playerid] [4], 1);
	TextDrawBoxColor(captcha_txt [playerid] [4], 255);
	TextDrawTextSize(captcha_txt [playerid] [4], 160.000000, -62.000000);

	captcha_txt [playerid] [5] = TextDrawCreate(540.000000, 198.000000, "G3");
	TextDrawAlignment(captcha_txt [playerid] [5], 3);
	TextDrawBackgroundColor(captcha_txt [playerid] [5], -1);
	TextDrawFont(captcha_txt [playerid] [5], 1);
	TextDrawLetterSize(captcha_txt [playerid] [5], 1.059999, 3.900000);
	TextDrawColor(captcha_txt [playerid] [5], color);
	TextDrawSetOutline(captcha_txt [playerid] [5], 1);
	TextDrawSetProportional(captcha_txt [playerid] [0], prop);
	TextDrawUseBox(captcha_txt [playerid] [5], 1);
	TextDrawBoxColor(captcha_txt [playerid] [5], 255);
	TextDrawTextSize(captcha_txt [playerid] [5], -120.000000, -52.000000);

	captcha_txt [playerid] [6] = TextDrawCreate(587.000000, 192.000000, "G4");
	TextDrawAlignment(captcha_txt [playerid] [6], 2);
	TextDrawBackgroundColor(captcha_txt [playerid] [6], -1);
	TextDrawFont(captcha_txt [playerid] [6], 1);
	TextDrawLetterSize(captcha_txt [playerid] [6], 0.799999, 3.899999);
	TextDrawColor(captcha_txt [playerid] [6], color);
	TextDrawSetOutline(captcha_txt [playerid] [6], 1);
	TextDrawSetProportional(captcha_txt [playerid] [0], prop);
	TextDrawUseBox(captcha_txt [playerid] [6], 1);
	TextDrawBoxColor(captcha_txt [playerid] [6], -16776961);
	TextDrawTextSize(captcha_txt [playerid] [6], 430.000000, -73.000000);

	captcha_txt [playerid] [7] = TextDrawCreate(605.000000, 232.000000, "G4");
	TextDrawAlignment(captcha_txt [playerid] [7], 2);
	TextDrawBackgroundColor(captcha_txt [playerid] [7], -1);
	TextDrawFont(captcha_txt [playerid] [7], 1);
	TextDrawLetterSize(captcha_txt [playerid] [7], 0.859999, 3.899999);
	TextDrawColor(captcha_txt [playerid] [7], color);
	TextDrawSetOutline(captcha_txt [playerid] [7], 1);
	TextDrawSetProportional(captcha_txt [playerid] [0], prop);
	TextDrawUseBox(captcha_txt [playerid] [7], 1);
	TextDrawBoxColor(captcha_txt [playerid] [7], -16776961);
	TextDrawTextSize(captcha_txt [playerid] [7], 380.000000, -62.000000);

	captcha_txt [playerid] [8] = TextDrawCreate(585.000000, 334.000000, "G5");
	TextDrawAlignment(captcha_txt [playerid] [8], 2);
	TextDrawBackgroundColor(captcha_txt [playerid] [8], -1);
	TextDrawFont(captcha_txt [playerid] [8], 1);
	TextDrawLetterSize(captcha_txt [playerid] [8], 0.859999, 3.899999);
	TextDrawColor(captcha_txt [playerid] [8], color);
	TextDrawSetOutline(captcha_txt [playerid] [8], 1);
	TextDrawSetProportional(captcha_txt [playerid] [0], prop);
	TextDrawUseBox(captcha_txt [playerid] [8], 1);
	TextDrawBoxColor(captcha_txt [playerid] [8], 65535);
	TextDrawTextSize(captcha_txt [playerid] [8], 410.000000, -92.000000);

	captcha_txt [playerid] [9] = TextDrawCreate(585.000000, 295.000000, "G5");
	TextDrawAlignment(captcha_txt [playerid] [9], 2);
	TextDrawBackgroundColor(captcha_txt [playerid] [9], -1);
	TextDrawFont(captcha_txt [playerid] [9], 1);
	TextDrawLetterSize(captcha_txt [playerid] [9], 0.859999, 3.899999);
	TextDrawColor(captcha_txt [playerid] [9], color);
	TextDrawSetOutline(captcha_txt [playerid] [9], 1);
	TextDrawSetProportional(captcha_txt [playerid] [9], prop);
	TextDrawUseBox(captcha_txt [playerid] [9], 1);
	TextDrawBoxColor(captcha_txt [playerid] [9], 65535);
	TextDrawTextSize(captcha_txt [playerid] [9], 410.000000, -92.000000);

	for(new i; i < sizeof(captcha_Txt[playerid]); i++) TextDrawShowForPlayer(playerid, captcha_Txt [playerod] [i]);

	return 1;

}

#endif

forward DestroyCaptcha(playerid), public DestroyCaptcha(playerid)
{
	for(new i; i < sizeof(captcha_Txt[playerid]); i++)
	{
		if(!captcha_Txt [playerid] [i]) continue; 
		TextDrawDestroy(captcha_Txt [playerid] [i]);
	}
	return 1;
} 

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    
	if (dialogid == CAPTCHA_DIALOG)
	{
		if(!response) // если нажал ESC
		{
			#if !defined CAPTCHA_WithoutConfig
				Kick(playerid);
			#else

			switch (captcha_exec) // решаем наказание
			{
				case 2: SendClientMessage(playerid, -1, CAPTCHA_BANNED), return Ban(playerid);
				case 3: return 1;
				case 4: return SetTimerEx(captcha_func_to_call, 100, false, "d", playerid);
				default: SendClientMessage(playerid, -1, CAPTCHA_KICKED), return Kick(playerid);
			}	
			#endif
		}
		new id = GetPVarInt(playerid, "Captcha_Quest");
		if(strcmp(inputtext, captcha_Answers [id], true)) return 1;
		else 
		{
			#if !defined CAPTCHA_WithoutConfig
				Kick(playerid);
			#else

			switch (captcha_exec) // решаем наказание
			{
				case 2: SendClientMessage(playerid, -1, CAPTCHA_BANNED), return Ban(playerid);
				case 3: return 1;
				case 4: return SetTimerEx(captcha_func_to_call, 100, false, "d", playerid);
				default: SendClientMessage(playerid, -1, CAPTCHA_KICKED), return Kick(playerid);
			}	
			#endif
		}
	}

    #if defined CAPTCHA_OnDialogResponse
        return CAPTCHA_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif
#define OnDialogResponse CAPTCHA_OnDialogResponse
#if defined CAPTCHA_OnDialogResponse
forward CAPTCHA_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif


public OnGameModeInit()
{

	#if !defined CAPTCHA_WithoutConfig // Работает ли режим с конфигурацией

		if(!ini_OpenFile("Captcha Config")) captcha_file = ini_OpenFile("Captcha Config"); // проверяем наличие файла и если он есть, то открываем
		else captcha_file = ini_CreateFile("Captcha Config", "ExecuteMode = Kick"); // иначе создаем его
		
		new temp_captcha_String[8]; // переменная для передачи наказания
		ini_getString(captcha_file, "ExecuteMode", temp_captcha_String); // Берем наказание

		switch(temp_captcha_String) // Распределяем
		{
			case "Kick": captcha_exec = 1; // 1 - Kick
			case "Ban": captcha_exec = 2; // 2 - Ban
			case "Ignore": captcha_exec = 3; // 3 - Игнорирование
			case "Call": {
				captcha_exec = 4; // 4 - вызов функции
				ini_getString(captcha_file, "FuncToCall", temp_captcha_String); // достаем функцию
			}
			default: captcha_exec = 1; // По стандарту кик
		}
		// Добавить настройки

	#endif

    #if defined CAPTCHA_OnGamemodeInit
        return CAPTCHA_OnGamemodeInit();
    #else
        return 1;
    #endif
}

#if defined _ALS_OnGamemodeInit
    #undef OnGamemodeInit
#else
    #define _ALS_OnGamemodeInit
#endif
#define OnGamemodeInit CAPTCHA_OnGamemodeInit
#if defined CAPTCHA_OnGamemodeInit
forward CAPTCHA_OnGamemodeInit();
#endif



