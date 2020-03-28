#pragma once

Ped createPed(char* model, Vector3 pos, float heading = 0);
Ped createPedOnHorse(char* model, Ped horse, int seatIndex = 1);
bool isPedHogtied(Ped ped);
void playAmbientSpeech(Ped ped, char* speechName, char* voice);