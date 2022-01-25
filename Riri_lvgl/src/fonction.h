#ifndef fonction_h
#define fonction_h

char action[256];

void fonction();

void fonction()
{
   getAction(action);
  if (strcmp(action, "") != 0) {

    Serial.println(action);

    if (strcmp(action, "Please") == 0)          Serial.println("\t->Thanks!");
    if (strcmp(action, LV_SYMBOL_RIGHT) == 0)   Serial.println("\t->Right");
    if (strcmp(action, LV_SYMBOL_LEFT) == 0)    Serial.println("\t->Left");
  }  
}



#endif