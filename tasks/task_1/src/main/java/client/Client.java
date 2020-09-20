package client;

import common.SerializationUtil;
import common.ServerHostData;
import common.Student;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public final class Client {

    public void run(String address, int port) throws IOException {
        SocketChannel client = SocketChannel.open(
               new InetSocketAddress(address, port)
        );
        client.configureBlocking(false);
        Student student = new Student("Gagarin", 30, 180);
        ByteBuffer buffer = ByteBuffer.wrap(SerializationUtil.serialize(student));
        client.write(buffer);
        client.close();
    }

    public static void main(String[] args) {
        try {
            new Client().run(ServerHostData.ADDRESS, ServerHostData.PORT);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
