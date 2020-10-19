package server;

import common.ServerHostData;

import java.io.IOException;
import java.io.PrintStream;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Iterator;
import java.util.Set;
import java.util.concurrent.*;

public class Server {
    private ServerSocketChannel serverChannel;
    private Selector selector;
    private final ExecutorService executor;
    private final Storage storage;

    private volatile boolean running;

    public Server() {
        int cores = Runtime.getRuntime().availableProcessors();
        executor = Executors.newFixedThreadPool(cores);
        storage = new Storage();
    }

    protected void stopServer() {
        running = false;
    }
    protected void setup(String address, int port) throws IOException {
        serverChannel = ServerSocketChannel.open();
        serverChannel.socket().bind(new InetSocketAddress(address, port));
        serverChannel.configureBlocking(false);
        selector = Selector.open();
        int ops = serverChannel.validOps();
        SelectionKey selectKey = serverChannel.register(selector, ops, null);
    }

    protected void processKeys() throws IOException {
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

    /**
     *
     * @param address adress to run server on
     * @param port port to run server on
     * @param secondsTimeout if < 1 - server runs endless,
     *                           else stops after time in seconds set here
     * @throws IOException
     */
    public void run(String address, int port, long secondsTimeout) throws IOException, InterruptedException {
        running = true;
        setup(address, port);

        ExecutorService executor = Executors.newFixedThreadPool(1);

        Future<?> future = executor.submit(new Runnable() {
            @Override
            public void run() {
                while (running) {
                    try {
                        processKeys();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        executor.shutdown();

        if (secondsTimeout > 0) {
            try {
                future.get(secondsTimeout, TimeUnit.SECONDS);
            } catch (TimeoutException e) {
                stopServer();
                future.cancel(true);
            } catch (ExecutionException e) {
                e.printStackTrace();
            }
        } else {
            while(!executor.awaitTermination(1, TimeUnit.SECONDS)) {
                Thread.sleep(1000);
            }
        }

        if(!executor.awaitTermination(2, TimeUnit.SECONDS)){
            executor.shutdownNow();
        }
        executor.shutdownNow();

        serverChannel.close();

    }

    protected void acceptConnection() throws IOException {
        SocketChannel clientChannel = serverChannel.accept();
        clientChannel.configureBlocking(false);
        clientChannel.register(selector, SelectionKey.OP_READ);
    }

    protected void readBuffer(SelectionKey key) throws IOException {
        SocketChannel clientChannel = (SocketChannel) key.channel();
        ByteBuffer buffer = ByteBuffer.allocate(1024);

        clientChannel.read(buffer);

        executor.submit(new DataProcessor(storage, buffer.array()));

        key.cancel();
    }


    public static void main(String[] args) {
        try {
            new Server().run(ServerHostData.ADDRESS, ServerHostData.PORT, 0);
        } catch (Exception ex) {
            Logger.log(System.err, ex.getMessage());
        }

    }

}

final class Logger {
    public static synchronized void log(PrintStream os, Object... logged) {
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
        LocalDateTime now = LocalDateTime.now();
        os.print("[LOGGED: " + dtf.format(now) + "] ");
        for (Object row : logged) {
            os.println(row);
        }
    }

}



