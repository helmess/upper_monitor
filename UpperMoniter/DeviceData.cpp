/*
 * DeviceData.c: 串口数据解析
 *
 * (C) Copyright SCU
 * Author: GGZ
 */
#include "DeviceData.h"

DeviceData::DeviceData(std::string ComData){
    std::string head = {0x1B, 0x40};    //数据包的头
    
    if( ComData.find(head, 0) != 0){
        std::cout << "data error" << std::endl;
        return;
    }
    int left = head.length();
    int right = 0;
    std::string cur={0x0a,0x1C, 0x26};

    right = ComData.find(cur, left);
    std::string t = ComData.substr(left, right - left);

    left = right + cur.length();
    cur = {0x0d,0x1C, 0x2e};
    right = ComData.find(cur, left);
    this->EventDescription = ComData.substr(left, right - left);

    left = right + cur.length();
    cur = {0x1C, 0x26};
    left = ComData.find(cur, left);
    left = left + cur.length();
    cur = {0x1c, 0x2e};
    right = ComData.find(cur, left);
    this->Event = ComData.substr(left, right - left);

    left = right + cur.length();
    cur = {0x1B, 0x69, 0x01};
    left = ComData.find(cur, left);
    left = left + cur.length();
    cur = {0x1B, 0x69};
    right = ComData.find(cur, left);
    this->Event = this->Event + ComData.substr(left, right - left);


    left = right + cur.length();
    cur = {0x1C, 0x26};
    left = ComData.find(cur, left);
    left = left + cur.length();
    cur = {0x1c, 0x2e};
    right = ComData.find(cur, left);
    this->EventDescription = ComData.substr(left, right - left) + this->EventDescription;

    left = 0;
    cur = {0x20, 0x20, 0x20};
    right = t.find(cur, 0);
    this->Date = t.substr(left, right - left);

    left = right + cur.length();
    right = t.find(cur, left);
    this->Time = t.substr(left, right - left);

 
    this->NetAddress = t.substr(t.length()-8,3);
    this->Loop = t.substr(t.length()-5, 2);
    this->DeviceAddress = t.substr(t.length()-3, 3);

}






// {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x38, 0x3A, 0x35, 0x34, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x30, 0x30, 0x34, 0x0A, 0x1C, 0x26, 0xB9, 0xE2, 0xBE, 0xAF, 0xB1, 0xA8, 0xC6, 0xF7, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xC7, 0xEB, 0xC7, 0xF3, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x30, 0x31, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0x20, 0xC9, 0xF9, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};

// {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x38, 0x3A, 0x35, 0x34, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x30, 0x30, 0x35, 0x0A, 0x1C, 0x26, 0xC8, 0xDC, 0xBD, 0xBA, 0xC3, 0xF0, 0xBB, 0xF0, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xC7, 0xEB, 0xC7, 0xF3, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x30, 0x32, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0x20, 0xC6, 0xF8, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};

// {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x38, 0x3A, 0x35, 0x34, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x30, 0x30, 0x36, 0x0A, 0x1C, 0x26, 0xC8, 0xDC, 0xBD, 0xBA, 0xC3, 0xF0, 0xBB, 0xF0, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xC7, 0xEB, 0xC7, 0xF3, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x30, 0x33, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0x20, 0xC6, 0xF8, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};

// {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x38, 0x3A, 0x35, 0x35, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x30, 0x30, 0x35, 0x0A, 0x1C, 0x26, 0xC8, 0xDC, 0xBD, 0xBA, 0xC3, 0xF0, 0xBB, 0xF0, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xC7, 0xEB, 0xC7, 0xF3, 0xCF, 0xFB, 0xB3, 0xFD, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x30, 0x31, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0x20, 0xC6, 0xF8, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};

// {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x38, 0x3A, 0x35, 0x36, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x30, 0x30, 0x36, 0x0A, 0x1C, 0x26, 0xC8, 0xDC, 0xBD, 0xBA, 0xC3, 0xF0, 0xBB, 0xF0, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xC7, 0xEB, 0xC7, 0xF3, 0xCF, 0xFB, 0xB3, 0xFD, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x30, 0x32, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0x20, 0xC6, 0xF8, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};

// {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x38, 0x3A, 0x35, 0x34, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x33, 0x32, 0x36, 0x0A, 0x1C, 0x26, 0xB0, 0xE5, 0xB0, 0xB4, 0xC5, 0xA5, 0xC6, 0xF4, 0xB6, 0xAF, 0xB7, 0xC5, 0xC6, 0xF8, 0x20, 0x20, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xB7, 0xB4, 0xC0, 0xA1, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x30, 0x33, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0xC3, 0xE6, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};

// {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x38, 0x3A, 0x35, 0x34, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x33, 0x32, 0x37, 0x0A, 0x1C, 0x26, 0xC6, 0xF8, 0xB5, 0xB9, 0xBC, 0xC6, 0xCA, 0xB1, 0xBF, 0xAA, 0xCA, 0xBC, 0x20, 0x20, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xB7, 0xB4, 0xC0, 0xA1, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x30, 0x34, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0xB7, 0xC5, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};

// {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x38, 0x3A, 0x35, 0x39, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x33, 0x33, 0x30, 0x0A, 0x1C, 0x26, 0xC6, 0xF8, 0xB5, 0xB9, 0xBC, 0xC6, 0xCA, 0xB1, 0xBD, 0xE1, 0xCA, 0xF8, 0x20, 0x20, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xB7, 0xB4, 0xC0, 0xA1, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x30, 0x35, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0xB7, 0xC5, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};

// {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x38, 0x3A, 0x35, 0x39, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x33, 0x33, 0x31, 0x0A, 0x1C, 0x26, 0xB6, 0xAF, 0xC6, 0xF8, 0xCC, 0xE5, 0xC5, 0xE7, 0xC8, 0xF7, 0x20, 0x20, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xB7, 0xB4, 0xC0, 0xA1, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x30, 0x36, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0xC6, 0xF4, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};

// {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x38, 0x3A, 0x35, 0x39, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x33, 0x33, 0x32, 0x0A, 0x1C, 0x26, 0xC6, 0xF8, 0xCD, 0xEA, 0xB3, 0xC9, 0x20, 0x20, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xB7, 0xB4, 0xC0, 0xA1, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x30, 0x37, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0xB7, 0xC5, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};

// {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x39, 0x3A, 0x31, 0x39, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x33, 0x33, 0x33, 0x0A, 0x1C, 0x26, 0xC6, 0xF8, 0xB5, 0xB9, 0xBC, 0xC6, 0xCA, 0xB1, 0xBD, 0xE1, 0xCA, 0xF8, 0x20, 0x20, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xB7, 0xB4, 0xC0, 0xA1, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x30, 0x38, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0xB7, 0xC5, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};

// {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x39, 0x3A, 0x31, 0x39, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x33, 0x33, 0x34, 0x0A, 0x1C, 0x26, 0xB6, 0xAF, 0xC6, 0xF8, 0xCC, 0xE5, 0xC5, 0xE7, 0xC8, 0xF7, 0x20, 0x20, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xB7, 0xB4, 0xC0, 0xA1, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x30, 0x39, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0xC6, 0xF4, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};

// {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x39, 0x3A, 0x31, 0x39, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x33, 0x33, 0x35, 0x0A, 0x1C, 0x26, 0xC6, 0xF8, 0xCD, 0xEA, 0xB3, 0xC9, 0x20, 0x20, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xB7, 0xB4, 0xC0, 0xA1, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x31, 0x30, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0xB7, 0xC5, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};
unsigned char data[] = {0x1B, 0x40, 0x32, 0x30, 0x32, 0x32, 0x2E, 0x30, 0x35, 0x2E, 0x32, 0x30, 0x20, 0x20, 0x20, 0x31, 0x34, 0x3A, 0x34, 0x38, 0x3A, 0x35, 0x34, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30, 0x31, 0x33, 0x32, 0x36, 0x0A, 0x1C, 0x26, 0xB0, 0xE5, 0xB0, 0xB4, 0xC5, 0xA5, 0xC6, 0xF4, 0xB6, 0xAF, 0xB7, 0xC5, 0xC6, 0xF8, 0x20, 0x20, 0x0D, 0x1C, 0x2E, 0x1B, 0x69, 0x01, 0x1C, 0x26, 0xB7, 0xB4, 0xC0, 0xA1, 0x1C, 0x2E, 0x1B, 0x69, 0x00, 0x1B, 0x69, 0x01, 0x30, 0x30, 0x33, 0x1B, 0x69, 0x00, 0x1B, 0x6C, 0x0C, 0x1C, 0x26, 0xC6, 0xF8, 0xCC, 0xE5, 0xC7, 0xF8, 0x20, 0xC3, 0xE6, 0x1C, 0x2E, 0x0D, 0x1B, 0x6C, 0x00, 0x0D, 0x0A};

int test(){
    for (int i = 0; i < sizeof(data); ++i)      //去除'\0'
        if(data[i]==0x00)
            data[i] = 0xff;

    std::string b((char *)(data));
    DeviceData a(b);
    
    std::cout << a.Event << std::endl;
    std::cout << a.EventDescription << std::endl;
    std::cout << a.Date << std::endl;
    std::cout << a.Time << std::endl;
    
    std::cout << a.NetAddress << std::endl;
    std::cout << a.Loop << std::endl;
    std::cout << a.DeviceAddress << std::endl;
    return 0;
}