import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * Implementacja semafora binarnego za pomocą kanałów i komunikatów.
 * 
 * Semafor binarny może przyjmować tylko dwie wartości: 0 (zablokowany) lub 1 (odblokowany).
 * Implementacja wykorzystuje BlockingQueue jako kanał komunikacyjny.
 */
public class BinarySemaphore {
    // Kanał komunikacyjny reprezentowany przez kolejkę blokującą
    private final BlockingQueue<Integer> channel;
    
    /**
     * Tworzy nowy semafor binarny.
     * 
     * @param initialValue początkowa wartość semafora (0 - zablokowany, 1 - odblokowany)
     * @throws IllegalArgumentException jeśli wartość początkowa nie jest 0 lub 1
     */
    public BinarySemaphore(int initialValue) {
        if (initialValue != 0 && initialValue != 1) {
            throw new IllegalArgumentException("Wartość początkowa semafora binarnego musi być 0 lub 1");
        }
        
        this.channel = new LinkedBlockingQueue<>(1); // Kanał o pojemności 1
        
        if (initialValue == 1) {
            try {
                // Jeśli semafor ma być początkowo odblokowany, umieszczamy token w kanale
                channel.put(1);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
    
    /**
     * Operacja P (wait/acquire) - blokuje semafor.
     * Jeśli semafor jest już zablokowany, wątek zostanie wstrzymany do momentu odblokowania.
     * 
     * @throws InterruptedException jeśli wątek zostanie przerwany podczas oczekiwania
     */
    public void P() throws InterruptedException {
        // Próba pobrania tokena z kanału - jeśli kanał jest pusty, wątek zostanie zablokowany
        channel.take();
    }
    
    /**
     * Operacja V (signal/release) - odblokowuje semafor.
     * 
     * @throws InterruptedException jeśli wątek zostanie przerwany podczas operacji
     */
    public void V() throws InterruptedException {
        // Próba umieszczenia tokena w kanale - jeśli kanał jest pełny, wątek zostanie zablokowany
        // W przypadku semafora binarnego, kanał ma pojemność 1, więc operacja V nie zadziała,
        // jeśli semafor jest już odblokowany
        if (channel.isEmpty()) {
            channel.put(1);
        }
    }
    
    /**
     * Sprawdza, czy semafor jest aktualnie odblokowany.
     * 
     * @return true jeśli semafor jest odblokowany, false w przeciwnym przypadku
     */
    public boolean isAvailable() {
        return !channel.isEmpty();
    }
} 