/*
    Lesson.h
    Author: RanaSystems
    Created: 10 Mar 2024
    Updated: 15 Mar 2024
*/

// we need a function to comnpare two lesson objects
#pragma once
#include <iostream>
#include "Date.h"

class Lesson
{
private:
    int lessonID;
    int instructorID; 
    int learnerID;        
    Date date;
    std::string lessonType;
    std::string lessonStatus;
    std::string lessonNote;

public:
    Lesson(int lessonID, Date date, std::string lessonType, std::string lessonStatus, std::string lessonNote, int instructorID, int learnerID);

    int getLessonID() const;
    int getInstructorID() const;
    void setInstructorID(int id);
    int getLearnerID() const;
    void setLearnerID(int id);
    Date getLessonDate() const;
    void setLessonDate(Date date);
    std::string getLessonType() const;
    void setLessonType(std::string lessonType);
    std::string getLessonStatus() const;
    void setLessonStatus(std::string lessonStatus);
    std::string getLessonNote() const;
    void setLessonNote(std::string lessonNote);
    static bool compareLesson(const Lesson& lesson1, const Lesson& lesson2);
};

