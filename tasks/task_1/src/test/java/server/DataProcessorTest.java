package server;

import common.SerializationUtil;
import common.Student;
import org.junit.Test;

import java.io.IOException;

import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.mock;

public class DataProcessorTest {

    @Test
    public void testRunMethod() throws IOException {

        Storage mock = mock(Storage.class);
        Student student = new Student("Name", 20, 180);
        DataProcessor tested = new DataProcessor(
                mock, SerializationUtil.serialize(student));

        tested.run();

        verify(mock).add(student);
    }
}
