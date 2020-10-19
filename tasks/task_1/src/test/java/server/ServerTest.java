package server;

import client.Client;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.Timeout;
import org.mockito.ArgumentCaptor;

import java.io.IOException;
import java.nio.channels.SelectionKey;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

import static org.mockito.Mockito.*;

public class ServerTest {

    private final String TEST_HOST = "localhost";
    private final int TEST_PORT = 8008;

    @Rule
    public Timeout globalTimeout = Timeout.seconds(25);

    @Test
    public void verifySetupMethodCall() throws IOException, InterruptedException {
        Server serverMock = spy(new Server());

        serverMock.run(TEST_HOST, TEST_PORT, 2);

        verify(serverMock).setup(TEST_HOST, TEST_PORT);

        verify(serverMock).stopServer();
    }

    @Test
    public void verifyAcceptAndReadMethodCall() throws IOException, InterruptedException {
        Server serverMock = spy(new Server());

        ExecutorService executor = Executors.newFixedThreadPool(2);

        Future<?> serverFuture = executor.submit(new Runnable() {
            @Override
            public void run() {
                try {
                    serverMock.run(TEST_HOST, TEST_PORT + 1, 5);
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        Thread.sleep(1000);

        Future<?> clientFuture = executor.submit(new Runnable() {
            @Override
            public void run() {
                try {
                    new Client().run(TEST_HOST, TEST_PORT + 1);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        executor.shutdown();

        if (!executor.awaitTermination(15, TimeUnit.SECONDS)) {
            serverFuture.cancel(true);
            clientFuture.cancel(true);
            executor.shutdownNow();
        }

        verify(serverMock).run(TEST_HOST, TEST_PORT + 1, 5);

        verify(serverMock, atLeastOnce()).processKeys();

        verify(serverMock).acceptConnection();

        final ArgumentCaptor<SelectionKey> captor = ArgumentCaptor.forClass(SelectionKey.class);

        verify(serverMock).readBuffer(captor.capture());

        SelectionKey key = captor.capture();
        // That's impossible to get channel out of this key now,
        // because client has already been disconnected and server stopped.
        // However this test shows that readBuffer was called with SelectionKey!

    }
}
