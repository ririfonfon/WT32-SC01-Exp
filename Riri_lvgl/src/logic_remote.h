#ifndef logic_remote_h
#define logic_remote_h

#include "Arduino.h"

char action[256];

uint8_t c_i_1;
uint16_t ch_input_1;
uint8_t char_input_1[2];
uint8_t c_i_2;
uint16_t ch_input_2;
uint8_t char_input_2[2];
uint8_t d_i_3;
uint16_t dim_input_3;
uint8_t char_input_3[2];

int8_t fonction_call;
int8_t old_fonction_call;

uint8_t clear_time;
bool selection[513];

bool check = true;

void init_variable();
void key(uint8_t key_value);
void remote_call();
void copyDMXToOutput(void);
void output_call();

void init_variable()
{
  for (int i = 0; i <= 513; i++)
  {
    selection[i] = false;
    output[i] = 0;
  }

  c_i_1 = 0;
  c_i_2 = 0;
  ch_input_1 = 0;
  ch_input_2 = 0;
  dim_input_3 = 0;
  fonction_call = -3;
  old_fonction_call = 0;
  clear_time = 0;

  lv_textarea_add_text(ta, " Ch : ");
}

void remote_call()
{
  getAction(action);
  if (strcmp(action, "") != 0)
  {
    Serial.println(action);

    if (strcmp(action, "0") == 0)
    {
      key(0);
    }
    else if (strcmp(action, "1") == 0)
    {
      key(1);
    }
    else if (strcmp(action, "2") == 0)
    {
      key(2);
    }
    else if (strcmp(action, "3") == 0)
    {
      key(3);
    }
    else if (strcmp(action, "4") == 0)
    {
      key(4);
    }
    else if (strcmp(action, "5") == 0)
    {
      key(5);
    }
    else if (strcmp(action, "6") == 0)
    {
      key(6);
    }
    else if (strcmp(action, "7") == 0)
    {
      key(7);
    }
    else if (strcmp(action, "8") == 0)
    {
      key(8);
    }
    else if (strcmp(action, "9") == 0)
    {
      key(9);
    }
    else if (strcmp(action, "  +") == 0)
    {
      fonction_call = -1;
      lv_textarea_add_text(ta, " + ");
      key(10);
    }
    else if (strcmp(action, "-") == 0)
    {
      fonction_call = -2;
      lv_textarea_add_text(ta, " - ");
      key(11);
    }
    else if (strcmp(action, "Thru") == 0)
    {
      fonction_call = 1;
      if (old_fonction_call == -2)
      {
        fonction_call = 4;
      }
      lv_textarea_add_text(ta, " Thru ");
      key(12);
    }
    else if (strcmp(action, "At") == 0)
    {
      fonction_call = 2;
      lv_textarea_add_text(ta, " At ");
      key(13);
    }
    else if (strcmp(action, "Please") == 0)
    {
      fonction_call = 3;
      if (old_fonction_call == 2)
      {
        fonction_call = 5;
      }
      clear_time = 0;
      lv_textarea_add_text(ta, " Please ");
      key(14);
    }
    else if (strcmp(action, "Clear") == 0)
    {
      key(15);
    }
    else if (strcmp(action, "If") == 0)
    {
      lv_textarea_add_text(ta, " if ");
      key(16);
    }
    else if (strcmp(action, "Full") == 0)
    {
      lv_textarea_add_text(ta, " Full ");
      key(17);
    }
    else if (strcmp(action, "Zero") == 0)
    {
      lv_textarea_add_text(ta, " Zero ");
      key(18);
    }
    else if (strcmp(action, "Half") == 0)
    {
      lv_textarea_add_text(ta, " Half ");
      key(19);
    }
    else if (strcmp(action, "-10") == 0)
    {
      lv_textarea_add_text(ta, " -10 ");
      key(20);
    }
    else if (strcmp(action, "+10") == 0)
    {
      lv_textarea_add_text(ta, " +10 ");
      key(21);
    }
  }
}
void key(uint8_t key_value)
{
  //     **  **  ******  **   **      ******    **      ******
  //     ** **   **       ** **       **  **      **    **  **
  //     ****    ****      ***        **  **  ********  ******
  //     ** **   **         *         **  **      **        **
  //     **  **  ******     *         ******    **      ******

  if ((key_value >= 0) && (key_value <= 9))
  {
    bool good;

    if (fonction_call < 1)
    {
      Serial.println(" if (fonction_call < 1) ");
      if (fonction_call == 0)
      {
        Serial.println(" if (fonction_call == 0) ");
        for (int i = 1; i <= 512; i++)
        {
          selection[i] = false;
        }
        fonction_call = -3;
        c_i_1 = 0;
      }
      if (c_i_1 == 0)
      {
        char_input_1[0] = key_value;
        ch_input_1 = char_input_1[0];
        good = true;
        c_i_1++;
      }
      else if (c_i_1 == 1)
      {
        char_input_1[1] = key_value;
        ch_input_1 = char_input_1[0] * 10 + char_input_1[1];
        good = true;
        c_i_1++;
      }
      else if (c_i_1 == 2)
      {
        char_input_1[2] = key_value;
        ch_input_1 = char_input_1[0] * 100 + char_input_1[1] * 10 + char_input_1[2];
        good = true;
        c_i_1++;
      }
      else if (c_i_1 > 2)
      {
        lv_textarea_add_char(ta, '\n');
        lv_textarea_set_text(ta, " TOO MANY NUMBER");
        lv_textarea_add_char(ta, '\n');
        good = false;
        c_i_1 = 0;
        ch_input_1 = 0;
      }
    }
    else if (fonction_call == 1 || fonction_call == 4)
    {
      Serial.println(" else if (fonction_call == 1 || fonction_call == 4) ");
      if (c_i_2 == 0)
      {
        char_input_2[0] = key_value;
        ch_input_2 = char_input_2[0];
        good = true;
        c_i_2++;
      }
      else if (c_i_2 == 1)
      {
        char_input_2[1] = key_value;
        ch_input_2 = char_input_2[0] * 10 + char_input_2[1];
        good = true;
        c_i_2++;
      }
      else if (c_i_2 == 2)
      {
        char_input_2[2] = key_value;
        ch_input_2 = char_input_2[0] * 100 + char_input_2[1] * 10 + char_input_2[2];
        good = true;
        c_i_2++;
      }
      else if (c_i_2 > 2)
      {
        lv_textarea_add_char(ta, '\n');
        lv_textarea_set_text(ta, " TOO MANY NUMBER");
        lv_textarea_add_char(ta, '\n');
        good = false;
        c_i_2 = 0;
        ch_input_2 = 0;
      }
    }
    else if (fonction_call == 2)
    {
      Serial.println(" else if (fonction_call == 2) ");
      if (d_i_3 == 0)
      {
        char_input_3[0] = key_value;
        dim_input_3 = char_input_3[0];
        good = true;
        d_i_3++;
      }
      else if (d_i_3 == 1)
      {
        char_input_3[1] = key_value;
        dim_input_3 = char_input_3[0] * 10 + char_input_3[1];
        good = true;
        d_i_3++;
      }
      else if (d_i_3 == 2)
      {
        char_input_3[2] = key_value;
        dim_input_3 = char_input_3[0] * 100 + char_input_3[1] * 10 + char_input_3[2];
        good = true;
        d_i_3++;
      }
      else if (d_i_3 > 2)
      {
        lv_textarea_add_char(ta, '\n');
        lv_textarea_set_text(ta, " TOO MANY NUMBER");
        lv_textarea_add_char(ta, '\n');
        good = false;
        d_i_3 = 0;
        dim_input_3 = 0;
      }
    }
    if (good)
    {
      lv_textarea_add_text(ta, action);
    }
    else
    {
      lv_textarea_add_text(ta, " Ch : ");
    }
  }

  //    **  **  ******  **   **    ** ******    **      ** **  **
  //    ** **   **       ** **     ** **  **      **    ** **  **
  //    ****    ****      ***      ** **  **  ********  ** ******
  //    ** **   **         *       ** **  **      **    **     **
  //    **  **  ******     *       ** ******    **      **     **
  //
  //  ((key_value == 10) || (key_value == 11) || (key_value == 13) || (key_value == 14)
  //      plus                   moins                 At                    please

  else if ((key_value == 10) || (key_value == 11) || (key_value == 13) || (key_value == 14))
  {
    Serial.println(" else if ((key_value == 10) || (key_value == 11) || (key_value == 13) || (key_value == 14))");
    Serial.print(" | old_fonction_call : ");
    Serial.print(old_fonction_call);
    Serial.print(" | fonction_call : ");
    Serial.println(fonction_call);
    // if (old_fonction_call == -1 && fonction_call != 2) // plus != AT
    if (old_fonction_call == -1 || fonction_call == -1) //
    {
      Serial.println(" if (old_fonction_call == -1)");
      if (ch_input_1 <= 512)
      {
        Serial.println(" +++++++ ch +++++++++ ");
        selection[ch_input_1] = true;
        c_i_1 = 0;
        ch_input_1 = 0;
      }
      else if (ch_input_1 > 512)
      {
        lv_textarea_set_text(ta, "1 -> 512 MAX");
        lv_textarea_add_char(ta, '\n');
        lv_textarea_add_text(ta, " Ch : ");
        c_i_1 = 0;
        ch_input_1 = 0;
      }
    }
    else if (old_fonction_call == -2) // moins
    {
      Serial.println(" else if (old_fonction_call == -2) ");
      if (ch_input_1 <= 512 && ch_input_1 != 0)
      {
        Serial.println(" ------ ch -------- ");
        selection[ch_input_1] = false;
        c_i_1 = 0;
        ch_input_1 = 0;
      }
      else if (ch_input_1 > 512 || ch_input_1 < 1)
      {
        lv_textarea_set_text(ta, "1 -> 512 MAX");
        lv_textarea_add_char(ta, '\n');
        lv_textarea_add_text(ta, " Ch : ");
        c_i_1 = 0;
        ch_input_1 = 0;
      }
    }
    else if (old_fonction_call == 1) // thru
    {
      Serial.println(" ------ Thru -------- ");
      if (ch_input_1 < ch_input_2)
      {
        for (int i = ch_input_1; i <= ch_input_2; i++)
        {
          selection[i] = true;
        }
      }
      else if (ch_input_2 < ch_input_1)
      {
        for (int i = ch_input_2; i <= ch_input_1; i++)
        {
          selection[i] = true;
        }
      }
      c_i_1 = 0;
      c_i_2 = 0;
      ch_input_1 = 0;
      ch_input_2 = 0;
    }
    else if (old_fonction_call == 4) // moins Thru
    {
      Serial.println(" moins-- Thru ---moins ");
      if (ch_input_1 < ch_input_2)
      {
        for (int i = ch_input_1; i <= ch_input_2; i++)
        {
          selection[i] = false;
        }
      }
      else if (ch_input_2 < ch_input_1)
      {
        for (int i = ch_input_2; i <= ch_input_1; i++)
        {
          selection[i] = false;
        }
      }
      c_i_1 = 0;
      c_i_2 = 0;
      ch_input_1 = 0;
      ch_input_2 = 0;
    }
    else if (old_fonction_call == 2 && fonction_call == 3) // At Please
    {
      Serial.println(" else if (old_fonction_call == 2 && fonction_call == 3) ");

      if (ch_input_1 <= 255 && ch_input_1 >= 0)
      {
        for (int i = 1; i <= 512; i++)
        {
          if (selection[i])
          {
            output[i] = dim_input_3;
            Serial.print(" output[i] = ");
            Serial.println(i);
          }
        }
      }
      else if (ch_input_1 > 255 || ch_input_1 < 0)
      {
        lv_textarea_set_text(ta, "0 -> 255 MAX");
        lv_textarea_add_char(ta, '\n');
        lv_textarea_add_text(ta, " Ch : ");
        c_i_1 = 0;
        ch_input_1 = 0;
      }
    }
    else if (fonction_call == 2 && old_fonction_call != 2) // At != At
    {
      Serial.println(" else if (fonction_call == 2 && old_fonction_call != 2) ");

      if (ch_input_1 <= 512)
      {
        Serial.println("  at +++++++ ch *** ");
        selection[ch_input_1] = true;
        c_i_1 = 0;
        ch_input_1 = 0;
      }
      else if (ch_input_1 > 512)
      {
        lv_textarea_set_text(ta, "1 -> 512 MAX");
        lv_textarea_add_char(ta, '\n');
        lv_textarea_add_text(ta, " Ch : ");
        c_i_1 = 0;
        ch_input_1 = 0;
      }
    }
    else if (fonction_call == 2 && old_fonction_call == 2) // At At
    {
      lv_textarea_add_char(ta, '\n');
      lv_textarea_add_text(ta, " Send Ch : ");
      for (int i = 1; i <= 512; i++)
      {
        if (selection[i])
        {
          output[i] = 255;

          char ch[3];
          sprintf(ch, "%d", i);
          lv_textarea_add_char(ta, ch[0]);
          if (i > 9)
          {
            lv_textarea_add_char(ta, ch[1]);
            lv_textarea_add_char(ta, ch[2]);
          }
          lv_textarea_add_text(ta, " + ");
        }

        // selection[i] = false;
      }
      lv_textarea_del_char(ta);
      lv_textarea_del_char(ta);
      lv_textarea_del_char(ta);
      old_fonction_call = 0;
      fonction_call = 0;
      lv_textarea_add_text(ta, " AT Full");
      lv_textarea_add_char(ta, '\n');
      copyDMXToOutput();
    }
  }

  //    **  **  ******  **   **    **  ******
  //    ** **   **       ** **     **  **
  //    ****    ****      ***      **  ******
  //    ** **   **         *       **      **
  //    **  **  ******     *       **  ******

  else if (key_value == 15) // Clear
  {
    lv_textarea_add_char(ta, '\n');
    if (clear_time == 0)
    {
      for (int i = 1; i <= 512; i++)
      {
        selection[i] = false;
      }
      lv_textarea_add_text(ta, " Clear I selection ");
    }
    else if (clear_time == 1)
    {
      for (int i = 1; i <= 512; i++)
      {
        output[i] = 0;
      }
      lv_textarea_add_text(ta, " Clear II Output ");
      copyDMXToOutput();
    }
    clear_time++;
    if (clear_time >= 2)
    {
      clear_time = 0;
    }
    lv_textarea_add_char(ta, '\n');
    lv_textarea_add_text(ta, " Ch : ");
  }

  //    **  **  ******  **   **    **  ******
  //    ** **   **       ** **     **  **
  //    ****    ****      ***      **  ******
  //    ** **   **         *       **  **  **
  //    **  **  ******     *       **  ******

  else if (key_value == 16) // If
  {
    for (int i = 1; i <= 512; i++)
    {
      if (output[i] > 0)
      {
        selection[i] = true;
      }
    }
  }

  //    **  **  ******  **   **    ** ******    **      *****     **
  //    ** **   **       ** **     **     **      **       **     **
  //    ****    ****      ***      **     **  ********  *****     **
  //    ** **   **         *       **     **      **    **        **
  //    **  **  ******     *       **     **    **      *****     **

  else if (key_value >= 17 && key_value <= 21) // full zero half -10 +10
  {
    clear_time = 0;
    // if (old_fonction_call == -1 && fonction_call != 2) // plus != AT
    if (old_fonction_call <= 0) //
    {
      if (ch_input_1 <= 512)
      {
        Serial.println(" **full zero half** add selection ");
        selection[ch_input_1] = true;
        c_i_1 = 0;
        ch_input_1 = 0;
      }
      else if (ch_input_1 > 512)
      {
        lv_textarea_set_text(ta, "1 -> 512 MAX");
        lv_textarea_add_char(ta, '\n');
        lv_textarea_add_text(ta, " Ch : ");

        c_i_1 = 0;
        ch_input_1 = 0;
      }
    }
    else if (old_fonction_call == 1) // Thru
    {
      Serial.println(" **full zero half** ------ Thru -------- ");
      if (ch_input_1 < ch_input_2)
      {
        Serial.println(" **< ");
        for (int i = ch_input_1; i <= ch_input_2; i++)
        {
          selection[i] = true;
        }
      }
      else if (ch_input_2 < ch_input_1)
      {
        Serial.println(" **>");
        for (int i = ch_input_2; i <= ch_input_1; i++)
        {
          selection[i] = true;
        }
      }
      c_i_1 = 0;
      c_i_2 = 0;
      ch_input_1 = 0;
      ch_input_2 = 0;
    }
    else if (old_fonction_call == 4) // moins Thru
    {
      Serial.println(" **full zero half** moins-- Thru ---moins ");
      if (ch_input_1 < ch_input_2)
      {
        for (int i = ch_input_1; i <= ch_input_2; i++)
        {
          selection[i] = false;
        }
      }
      else if (ch_input_2 < ch_input_1)
      {
        for (int i = ch_input_2; i <= ch_input_1; i++)
        {
          selection[i] = false;
        }
      }
      c_i_1 = 0;
      c_i_2 = 0;
      ch_input_1 = 0;
      ch_input_2 = 0;
    }

    c_i_1 = 0;
    c_i_2 = 0;
    ch_input_1 = 0;
    ch_input_2 = 0;
    old_fonction_call = fonction_call;
    fonction_call = 0;

    // lv_textarea_add_char(ta, '\n');
    // lv_textarea_add_text(ta, " Ch : ");
    // for (int i = 1; i <= 512; i++)
    // {
    //   if (selection[i])
    //   {
    //     char ch[3];
    //     sprintf(ch, "%d", i);
    //     lv_textarea_add_char(ta, ch[0]);
    //     if (i > 9)
    //     {
    //       lv_textarea_add_char(ta, ch[1]);
    //       lv_textarea_add_char(ta, ch[2]);
    //     }
    //     lv_textarea_add_text(ta, " + ");
    //   }
    // }
    // lv_textarea_del_char(ta);
    // lv_textarea_del_char(ta);
    // lv_textarea_del_char(ta);
    
    if (key_value == 17) // Full
    {
      lv_textarea_add_char(ta, '\n');
      lv_textarea_add_text(ta, " Send Ch : ");
      for (int i = 1; i <= 512; i++)
      {
        if (selection[i])
        {
          output[i] = 255;

          char ch[3];
          sprintf(ch, "%d", i);
          lv_textarea_add_char(ta, ch[0]);
          if (i > 9)
          {
            lv_textarea_add_char(ta, ch[1]);
            lv_textarea_add_char(ta, ch[2]);
          }
          lv_textarea_add_text(ta, " + ");
        }
        // selection[i] = false;
      }
      lv_textarea_del_char(ta);
      lv_textarea_del_char(ta);
      lv_textarea_del_char(ta);
      lv_textarea_add_text(ta, " AT Full");
      copyDMXToOutput();
    }
    else if (key_value == 18) // Zero
    {
      lv_textarea_add_char(ta, '\n');
      lv_textarea_add_text(ta, " Send Ch : ");
      for (int i = 1; i <= 512; i++)
      {
        if (selection[i])
        {
          output[i] = 0;

          char ch[3];
          sprintf(ch, "%d", i);
          lv_textarea_add_char(ta, ch[0]);
          if (i > 9)
          {
            lv_textarea_add_char(ta, ch[1]);
            lv_textarea_add_char(ta, ch[2]);
          }
          lv_textarea_add_text(ta, " + ");
        }
        // selection[i] = false;
      }
      lv_textarea_del_char(ta);
      lv_textarea_del_char(ta);
      lv_textarea_del_char(ta);
      lv_textarea_add_text(ta, " AT Zero");
      copyDMXToOutput();
    }
    else if (key_value == 19) // Half
    {
      lv_textarea_add_char(ta, '\n');
      lv_textarea_add_text(ta, " Send Ch : ");
      for (int i = 1; i <= 512; i++)
      {
        if (selection[i])
        {
          output[i] = 127;

          char ch[3];
          sprintf(ch, "%d", i);
          lv_textarea_add_char(ta, ch[0]);
          if (i > 9)
          {
            lv_textarea_add_char(ta, ch[1]);
            lv_textarea_add_char(ta, ch[2]);
          }
          lv_textarea_add_text(ta, " + ");
        }
        // selection[i] = false;
      }
      lv_textarea_del_char(ta);
      lv_textarea_del_char(ta);
      lv_textarea_del_char(ta);
      lv_textarea_add_text(ta, " AT 127");
      copyDMXToOutput();
    }
    else if (key_value == 20) // -10
    {
      lv_textarea_add_char(ta, '\n');
      lv_textarea_add_text(ta, " Send Ch : ");
      for (int i = 1; i <= 512; i++)
      {
        if (selection[i])
        {
          output[i] = output[i] - 10;
          if (output[i] < 0)
          {
            output[i] = 0;
          }
          char ch[3];
          sprintf(ch, "%d", i);
          lv_textarea_add_char(ta, ch[0]);
          if (i > 9)
          {
            lv_textarea_add_char(ta, ch[1]);
            lv_textarea_add_char(ta, ch[2]);
          }
          lv_textarea_add_text(ta, " + ");
        }
      }
      lv_textarea_del_char(ta);
      lv_textarea_del_char(ta);
      lv_textarea_del_char(ta);
      lv_textarea_add_text(ta, " AT -10");
      copyDMXToOutput();
    }
    else if (key_value == 21) // +10
    {
      lv_textarea_add_char(ta, '\n');
      lv_textarea_add_text(ta, " Send Ch : ");
      for (int i = 1; i <= 512; i++)
      {
        if (selection[i])
        {
          output[i] = output[i] + 10;
          if (output[i] > 255)
          {
            output[i] = 255;
          }
          char ch[3];
          sprintf(ch, "%d", i);
          lv_textarea_add_char(ta, ch[0]);
          if (i > 9)
          {
            lv_textarea_add_char(ta, ch[1]);
            lv_textarea_add_char(ta, ch[2]);
          }
          lv_textarea_add_text(ta, " + ");
        }
      }
      lv_textarea_del_char(ta);
      lv_textarea_del_char(ta);
      lv_textarea_del_char(ta);
      lv_textarea_add_text(ta, " AT +10");
      copyDMXToOutput();
    }
    lv_textarea_add_char(ta, '\n');
    lv_textarea_add_text(ta, " Ch : ");
  }

  //     ******  ******  *   **  ******     ******  ******  **      **
  //     **      **  **  **  **  **         **      **  **  **      **
  //     ****    **  **  *** **  **         **      ******  **      **
  //     **      **  **  ** ***  **         **      **  **  **      **
  //     **      ******  **  **  ******     ******  **  **  ******  ******

  if (fonction_call == 3) // Please
  {
    Serial.println(" list ch ");
    lv_textarea_add_char(ta, '\n');
    c_i_1 = 0;
    c_i_2 = 0;
    ch_input_1 = 0;
    ch_input_2 = 0;
    fonction_call = 0;
    old_fonction_call = 0;
    lv_textarea_add_text(ta, " Ch : ");
    for (int i = 1; i <= 512; i++)
    {
      if (selection[i])
      {
        char ch[3];
        sprintf(ch, "%d", i);
        lv_textarea_add_char(ta, ch[0]);
        if (i > 9)
        {
          lv_textarea_add_char(ta, ch[1]);
          lv_textarea_add_char(ta, ch[2]);
        }
        lv_textarea_add_text(ta, " + ");
      }
    }
    lv_textarea_del_char(ta);
    lv_textarea_del_char(ta);
    lv_textarea_del_char(ta);
  }
  else if (fonction_call == 5) // Please to At
  {
    Serial.println(" send ch ");
    lv_textarea_add_char(ta, '\n');
    c_i_1 = 0;
    c_i_2 = 0;
    ch_input_1 = 0;
    ch_input_2 = 0;
    fonction_call = 0;
    old_fonction_call = 0;
    lv_textarea_add_text(ta, " Send Ch : ");
    for (int i = 1; i <= 512; i++)
    {
      if (selection[i])
      {
        output[i] = dim_input_3;

        char ch[3];
        sprintf(ch, "%d", i);
        lv_textarea_add_char(ta, ch[0]);
        if (i > 9)
        {
          lv_textarea_add_char(ta, ch[1]);
          lv_textarea_add_char(ta, ch[2]);
        }
        lv_textarea_add_text(ta, " + ");
      }
      // selection[i] = false;
    }
    lv_textarea_del_char(ta);
    lv_textarea_del_char(ta);
    lv_textarea_del_char(ta);
    lv_textarea_add_text(ta, " AT ");
    char dim[3];
    sprintf(dim, "%d", dim_input_3);
    lv_textarea_add_char(ta, dim[0]);
    if (dim_input_3 > 9)
    {
      lv_textarea_add_char(ta, dim[1]);
      lv_textarea_add_char(ta, dim[2]);
    }
    d_i_3 = 0;
    dim_input_3 = 0;
    lv_textarea_add_char(ta, '\n');
    lv_textarea_add_text(ta, " Ch : ");
    copyDMXToOutput();
  }

  //    *****    ******  *****   **  **  ******
  //    **  **   **      **  **  **  **  **
  //    **   **  ****    *****   **  **  ** ***
  //    **  **   **      **  **  **  **  **  **
  //    *****    ******  *****   ******  ******
  Serial.print(" clear : ");
  Serial.print(clear_time);
  Serial.print(" ch 1 : ");
  Serial.print(ch_input_1);
  Serial.print(" | ch 2 : ");
  Serial.print(ch_input_2);
  Serial.print(" | dim : ");
  Serial.print(dim_input_3);
  Serial.print(" | old_fonction_call : ");
  Serial.print(old_fonction_call);
  Serial.print(" | fonction_call : ");
  Serial.println(fonction_call);
  for (int i = 1; i <= 512; i++)
  {
    if (selection[i])
    {
      Serial.print(" + CH : ");
      Serial.print(i);
    }
  }
  old_fonction_call = fonction_call;
}

//   ******    ****   ****  **    **
//   **   **   ** ** ** **   **  **
//   **    **  **  ***  **    ***
//   **   **   **   *   **   **  **
//   ******    **       **  **    **

void copyDMXToOutput(void)
{
  Serial.println("send dmx ");
  xSemaphoreTake(ESP32DMX1.lxDataLock, portMAX_DELAY);
  for (int i = 1; i <= 512; i++)
  {
    ESP32DMX1.setSlot(i, output[i]);
    if (output[i])
    {
      Serial.print(" CH : ");
      Serial.print(i);
      Serial.print(" = ");
      Serial.print(output[i]);
    }
  }
  Serial.println("");
  xSemaphoreGive(ESP32DMX1.lxDataLock);
}

//   ****  **  ** ****** *****  **  ** ******   ****** ****** **     **
//  **  ** **  **   **   **  ** **  **   **     **     **  ** **     **
//  **  ** **  **   **   *****  **  **   **     **     ****** **     **
//  **  ** **  **   **   **     **  **   **     **     **  ** **     **
//   ****   ****    **   **      ****    **     ****** **  ** ****** ******

void output_call()
{
  if (check)
  {
    check = false;
    statue = true;
    Serial.println("output_call() ");
    lv_textarea_set_text(tat, "");

    for (int i = 1; i <= 512; i++)
    {
      if (output[i])
      {
        lv_textarea_add_text(tat, " Ch : ");
        char ch[3];
        sprintf(ch, "%d", i);
        lv_textarea_add_char(tat, ch[0]);
        if (i > 9)
        {
          lv_textarea_add_char(tat, ch[1]);
          lv_textarea_add_char(tat, ch[2]);
        }
        lv_textarea_add_text(tat, " AT ");
        char dim[3];
        int gf = output[i];
        sprintf(dim, "%d", gf);
        lv_textarea_add_char(tat, dim[0]);
        if (gf > 9)
        {
          lv_textarea_add_char(tat, dim[1]);
          lv_textarea_add_char(tat, dim[2]);
        }
        lv_textarea_add_char(tat, '\n');
      }
    }
  }
}
#endif