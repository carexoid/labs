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

        Object[] arr = students.toArray();

        Student[] res = new Student[arr.length];

        int i = 0;

        for (Object student : arr) {
            res[i++] = (Student)student;
        }

        return res;
    }
}
