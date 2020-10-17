package server;

import common.Student;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class StorageTest {

    private Storage storage;

    private Student[] getArrayForTest() {
        return new Student[]{
                new Student("Daniil", 19, 186),
                new Student("Iluxa,", 19, 190),
                new Student("Chorniy", 25, 200)
        };
    }

    private void fillStorage(Student[] arr) {
        for (Student student : arr) {
            storage.add(student);
        }
    }

    @Before
    public void createEmptyStorage() {
        storage = new Storage();
    }

    @Test
    public void testEmptyToArray() {
        assertEquals(
                storage.toArray(),
                new Student[]{});
    }

    @Test
    public void testInsertingSomeStudents() {
        Student[] students = getArrayForTest();

        fillStorage(students);

        assertEquals(storage.toArray(), students);
    }

    @Test
    public void testGetMethod() {
        Student[] students = getArrayForTest();

        fillStorage(students);

        for (int i = 0; i < students.length; ++i) {
            assertEquals(students[i], storage.get(i));
        }
    }
}
