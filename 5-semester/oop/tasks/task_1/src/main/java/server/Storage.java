package server;

import common.Student;

import java.util.ArrayList;

public class Storage {
    private final ArrayList<Student> students;

    public Storage() {
        students = new ArrayList<>();
    }

    public synchronized void add(Student student) {
        students.add(student);
    }

    public synchronized Student get(int index) {
        return students.get(index);
    }

    public synchronized Student[] toArray() {
        return students.toArray(new Student[0]);
    }
}
