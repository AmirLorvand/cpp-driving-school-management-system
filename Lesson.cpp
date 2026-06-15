#include "Lesson.h"

Lesson::Lesson(int lessonID, Date date, std::string lessonType, std::string lessonStatus,std::string lessonNote, int instructorID, int learnerID)
    : lessonID(lessonID), date(date), lessonType(lessonType), lessonStatus(lessonStatus), lessonNote(lessonNote), instructorID(instructorID), learnerID(learnerID) {}

int Lesson::getLessonID() const{
    return lessonID;
}

int Lesson::getInstructorID() const {
    return instructorID;
}

void Lesson::setInstructorID(int id)
{
    instructorID = id;
}

int Lesson::getLearnerID() const {
    return learnerID;
}

void Lesson::setLearnerID(int id) {
    learnerID = id;
}

Date Lesson::getLessonDate() const{
    return date;
}

void Lesson::setLessonDate(Date date) {
    this->date = date;
}

std::string Lesson::getLessonType() const{
    return lessonType;
}

void Lesson::setLessonType(std::string lessonType) {
    this->lessonType = lessonType;
}

std::string Lesson::getLessonStatus() const {
    return lessonStatus;
}

void Lesson::setLessonStatus(std::string lessonStatus) {
    this->lessonStatus = lessonStatus;
}

std::string Lesson::getLessonNote() const {
    return lessonNote;
}

void Lesson::setLessonNote(std::string lessonNote) {
    this->lessonNote = lessonNote;
}

bool Lesson::compareLesson(const Lesson& lesson1, const Lesson& lesson2) {
    return lesson1.getLessonID() == lesson2.getLessonID();
}
