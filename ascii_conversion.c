///*
// * ascii_conversion.c
// *
// *  Created on: Nov 5, 2017
// *      Author: kwat1
// */
//
//
//
///*======================       Convert to ASCIII            ==============================*/
//
///*
// *  char ascii_distance[10] ={0,0,0,0,0,0,0,0,0,0};         //creates an ascii string representation for distance
//    char ascii_velocity[10];         //creates an ascii string representation for velocity
// * */
// void reverse(char str[], int len)        //function to reverse string to get it readable and not backwards
//{
//    int start, end;
//    char temp;
//    for (start=0, end = len-1; start<end; start++, end--)
//    {
//        temp = *(str+start);
//        *(str+start)= *(str+end);
//        *(str+end) = temp;
//    }
//}
//
// int intToStr(int value, char str[], int length)
//{
//    int i = 0;
//    while (value)
//    {
//        str[i++] = (value%10) + '0';
//        value = value/10;
//    }
//    while (i < length)
//    {
//        str[i++] = '0';
//    }
//    reverse(str,i);
//    str[i] = '\0';
//    return i;
//}
//
// char itoa (int value, char str[], int base)           //integer to string function
//{
//    int  i = 0;
//    int sign;
//
//    if ((sign = value) < 0){        //What to do if values is negative
//        value = -value;         //make value positive so we can work with
//    }
//
//    do{
//        str[i++] = value % base + '0';
//    }while ((value /= base) > 0);
//
//    if (sign < 0){
//        str[i++] = '-';
//    }
//    str[i] = '\0';
//    reverse(str,i);
//
//}
//
// char ftoa(float f, int afterpoint)           //float to string function
//{
//
//    int ipart = (int)f;
//
//    float fpart = f - (float)ipart;
//
//    int i = intToStr(ipart, str, 0);
//
//    if (afterpoint != 0)
//    {
//        str[i] = '.';
//
//        fpart = fpart * pow(10,afterpoint);
//
//        intToStr((int)fpart, str + i + 1, afterpoint);
//    }
//
//
//
//    return str;
//}
