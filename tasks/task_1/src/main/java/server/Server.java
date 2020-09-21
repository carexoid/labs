package server;

import common.SerializationUtil;
import common.ServerHostData;
import common.Student;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.charset.StandardCharsets;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;

public final class Server {
    private ServerSocketChannel serverChannel;
    private Selector selector;
    private final ExecutorService executor;
    private final Storage storage;

    public Server() {
        int cores = Runtime.getRuntime().availableProcessors();
        executor = Executors.newFixedThreadPool(cores);
        storage = new Storage();
    }

    private void setup(String address, int port) throws IOException {
        serverChannel = ServerSocketChannel.open();
        serverChannel.socket().bind(new InetSocketAddress(address, port));
        serverChannel.configureBlocking(false);
        selector = Selector.open();
        int ops = serverChannel.validOps();
        SelectionKey selectKey = serverChannel.register(selector, ops, null);
    }

    public void run(String address, int port) throws IOException {
        setup(address, port);

        while (true) {
            selector.select();
            Set<SelectionKey> keys = selector.selectedKeys();
            Iterator<SelectionKey> keyIter = keys.iterator();

            while (keyIter.hasNext()) {
                SelectionKey currentKey = keyIter.next();
                if (currentKey.isAcceptable()) {
                    acceptConnection();
                } else if (currentKey.isReadable()) {
                    readBuffer(currentKey);
                }
                keyIter.remove();
            }
        }
    }

    private void acceptConnection() throws IOException {
        SocketChannel clientChannel = serverChannel.accept();
        clientChannel.configureBlocking(false);
        clientChannel.register(selector, SelectionKey.OP_READ);
    }

    private void readBuffer(SelectionKey key) throws IOException {
        SocketChannel clientChannel = (SocketChannel) key.channel();
        ByteBuffer buffer = ByteBuffer.allocate(1024);

        clientChannel.read(buffer);

        executor.submit(new DataProcessor(storage, buffer.array()));

        key.cancel();
    }


    public static void main(String[] args) {
        try {
            new Server().run(ServerHostData.ADDRESS, ServerHostData.PORT);
        } catch (IOException ex) {
            Logger.log(ex.getMessage());
        }
    }

}

final class Logger {
    public static synchronized void log(Object... logged) {
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
        LocalDateTime now = LocalDateTime.now();
        System.err.print("[LOGGED: " + dtf.format(now) + "] ");
        for (Object row : logged) {
            System.err.println(row);
        }
    }

}

final class Storage {
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

    public synchronized Object[] toArray() {
        return students.toArray();
    }
}

final class DataProcessor implements Runnable {

    private final byte[] serializedData;
    private final Storage storage;

    public DataProcessor (Storage storage, byte[] serializedData) {
        this.serializedData = serializedData;
        this.storage = storage;
    }

    @Override
    public void run() {
        try {
            Student student = (Student) SerializationUtil.deserialize(serializedData);
            storage.add(student);
            Logger.log("Got new student: ", student);
        } catch (Exception ex) {
            Logger.log(Arrays.stream(ex.getStackTrace()).toArray());
        }
    }
}


