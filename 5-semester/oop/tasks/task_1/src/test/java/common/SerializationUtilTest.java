package common;

import org.junit.Test;

import java.io.IOException;
import java.util.ArrayList;

import static org.junit.Assert.assertEquals;

public class SerializationUtilTest {

    @Test
    public void TestWithArrayList()
            throws IOException, ClassNotFoundException {
        ArrayList<String> arr = new ArrayList<>();
        for (int i = 0; i < 1000; ++i) {
            arr.add("Some string " + i);
        }

        byte[] serialized = SerializationUtil.serialize(arr);

        assertEquals(arr, SerializationUtil.deserialize(serialized));
    }

    @Test
    public void TestWithStudent()
            throws IOException, ClassNotFoundException {
        Student student = new Student("Some name", 13, 130);

        byte[] serialized = SerializationUtil.serialize(student);

        assertEquals(student, SerializationUtil.deserialize(serialized));

    }
}
