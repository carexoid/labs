package common;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.Serializable;

public class Student implements Serializable {
    private final String name;
    private final int age;
    private final int height;

    public Student(String name, int age, int height) {
        this.name = name;
        this.age = age;
        this.height = height;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public int getHeight() {
        return height;
    }

    @Override
    public String toString() {
        return "Name: " + name +
                ", Age: " + age +
                ", Height: " + height;
    }

    @Override
    public boolean equals(Object other) {
        if (other == this) {
            return true;
        }
        if (other == null) {
            return false;
        }
        if (this.getClass() != other.getClass()) {
            return false;
        }
        Student otherStudent = (Student) other;
        return name.equals(otherStudent.name) &&
                age == otherStudent.age &&
                height == otherStudent.height;
    }

    @Override
    public int hashCode() {
        return age + height + (name == null ? 0 : name.hashCode());
    }
}