#ifndef fonction_h
#define fonction_h

char action[256];

uint8_t v_i_1;
uint16_t value_input_1;
uint8_t char_input_1[2];
uint8_t v_i_2;
uint16_t value_input_2;
uint8_t char_input_2[2];

int8_t fon;
int8_t old_fon;

bool select[512];
uint8_t output[512];

void init_variable();
void key(uint8_t key_value);
void fonction();

void init_variable()
{
  for (int i = 0; i <= 512; i++)
    select[i] = false;

  v_i_1 = 0;
  v_i_2 = 0;
  value_input_1 = 0;
  value_input_2 = 0;
  fon = 0;
  old_fon = 0;
}

void fonction()
{
  getAction(action);
  if (strcmp(action, "") != 0)
  {
    Serial.println(action);

    if (strcmp(action, "0") == 0)
    {
      key(0);
      Serial.println("\t->0");
    }
    else if (strcmp(action, "1") == 0)
    {
      key(1);
      Serial.println("\t->1");
    }
    else if (strcmp(action, "2") == 0)
    {
      key(2);
      Serial.println("\t->2");
    }
    else if (strcmp(action, "3") == 0)
    {
      key(3);
      Serial.println("\t->3");
    }
    else if (strcmp(action, "4") == 0)
    {
      key(4);
      Serial.println("\t->4");
    }
    else if (strcmp(action, "5") == 0)
    {
      key(5);
      Serial.println("\t->5");
    }
    else if (strcmp(action, "6") == 0)
    {
      key(6);
      Serial.println("\t->6");
    }
    else if (strcmp(action, "7") == 0)
    {
      key(7);
      Serial.println("\t->7");
    }
    else if (strcmp(action, "8") == 0)
    {
      key(8);
      Serial.println("\t->8");
    }
    else if (strcmp(action, "9") == 0)
    {
      key(9);
      Serial.println("\t->9");
    }
    else if (strcmp(action, "+") == 0)
    {
      fon = 0;
      key(10);
      Serial.println("\t->+");
    }
    else if (strcmp(action, "-") == 0)
    {
      fon = -1;
      key(11);
      Serial.println("\t->-");
    }
    else if (strcmp(action, "Thru") == 0)
    {
      fon = 1;
      key(12);
      Serial.println("\t->Thru");
    }
    else if (strcmp(action, "At") == 0)
    {
      fon = 2;
      key(13);
      Serial.println("\t->At");
    }
    else if (strcmp(action, "Please") == 0)
    {
      fon = 3;
      key(14);
          Serial.println("\t->Thanks!");
    }
    else if (strcmp(action, LV_SYMBOL_RIGHT) == 0)
    {
      Serial.println("\t->Right");
    }
    else if (strcmp(action, LV_SYMBOL_LEFT) == 0)
    {
      Serial.println("\t->Left");
    }
  }
}
void key(uint8_t key_value)
{
  if ((key_value >= 0) && (key_value <= 9))
  {
    if (v_i_1 == 0)
    {
      char_input_1[0] = key_value;
      value_input_1 = char_input_1[0];
      v_i_1++;
    }
    else if (v_i_1 == 1)
    {
      char_input_1[1] = key_value;
      value_input_1 = char_input_1[0] * 10 + char_input_1[1];
      v_i_1++;
    }
    else if (v_i_1 == 2)
    {
      char_input_1[2] = key_value;
      value_input_1 = char_input_1[0] * 100 + char_input_1[1] * 10 + char_input_1[2];
      v_i_1++;
    }
    lv_textarea_add_text(ta, action);
    Serial.print("value : ");
    Serial.print(value_input_1);
    Serial.print(" old_fon : ");
    Serial.print(old_fon);
    Serial.print(" fon : ");
    Serial.print(fon);

  }

  else if ((key_value == 10) && (key_value <= 11) || (key_value == 14))
  {
    if (old_fon == 0)
    {
      if (value_input_1 <= 512)
      {
        select[value_input_1] = true;
        v_i_1 = 0;
        value_input_1 = 0;
      }
      else if (value_input_1 > 512)
      {
        lv_textarea_add_text(ta, "512 MAX");
        lv_textarea_add_char(ta, '\n');
        v_i_1 = 0;
        value_input_1 = 0;
      }
    }
    else if (old_fon == -1)
    {
      if (value_input_1 <= 512)
      {
        select[value_input_1] = false;
        v_i_1 = 0;
        value_input_1 = 0;
      }
      else if (value_input_1 > 512)
      {
        lv_textarea_add_text(ta, "512 MAX");
        lv_textarea_add_char(ta, '\n');
        v_i_1 = 0;
        value_input_1 = 0;
      }
    }
    else if (old_fon == 1)
    {
    }
    else if (old_fon == 2)
    {
      if (value_input_1 <= 255)
      {

      }
      else if (value_input_1 > 255)
      {
        lv_textarea_add_text(ta, "255 MAX");
        lv_textarea_add_char(ta, '\n');
        v_i_1 = 0;
        value_input_1 = 0;
      }
    }
    else if (old_fon == 3)
    {
    }
    old_fon = fon;
  }
}

#endif