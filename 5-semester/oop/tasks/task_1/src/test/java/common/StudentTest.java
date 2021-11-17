package common;

import org.junit.Before;
import org.junit.Test;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.Random;

import static org.junit.Assert.*;

public class StudentTest {
    Student student;
    String name;
    int age;
    int height;

    @Before
    public void setupStudent() {
        Random rand = new Random();
        byte[] array = new byte[7];
        rand.nextBytes(array);
        name = new String(array, StandardCharsets.UTF_8);
        age = rand.nextInt();
        height = rand.nextInt();
        student = new Student(name, age, height);
    }

    @Test
    public void testingGetters() {
        assertEquals(name, student.getName());
        assertEquals(age, student.getAge());
        assertEquals(height, student.getHeight());
    }

    @Test
    public void testingToStringMethod() {
        String expectedString = "Name: " + name +
                ", Age: " + age +
                ", Height: " + height;

        assertEquals(expectedString, student.toString());
    }

    @Test
    public void testingEqualsMethod_expectingTrue() {
        assertTrue(student.equals(new Student(name, age, height)));
    }

    @Test
    public void testingEqualsMethod_expectingFalse() {
        assertFalse(student.equals(
                new Student(name + "some suffix", age, height)
        ));
        assertFalse(student.equals(new Student(name, age + 1, height)));
        assertFalse(student.equals(new Student(name, age, height + 1)));
    }

    @Test
    public void testingEqualsMethod_withNull() {
        assertFalse(student.equals(null));
    }

    @Test
    public void testingEqualsMethod_withObject() {
        assertFalse(student.equals(new Object()));
    }

    @Test
    public void testingHashCode() {
        assertEquals(student.hashCode(),
                new Student(name, age, height).hashCode());
    }
}
