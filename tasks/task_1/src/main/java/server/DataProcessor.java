package server;

import common.SerializationUtil;
import common.Student;

import java.util.Arrays;

public class DataProcessor implements Runnable {

    private final byte[] serializedData;
    private final Storage storage;

    public DataProcessor(Storage storage, byte[] serializedData) {
        this.serializedData = serializedData;
        this.storage = storage;
    }

    @Override
    public void run() {
        try {
            Student student = (Student) SerializationUtil.deserialize(serializedData);
            storage.add(student);
            Logger.log(System.out, "Got new student: ", student);
        } catch (Exception ex) {
            Logger.log(System.err, Arrays.stream(ex.getStackTrace()).toArray());
        }
    }
}



