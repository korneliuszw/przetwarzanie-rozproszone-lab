/**
 * Demonstracja użycia semafora binarnego do synchronizacji dostępu do zasobu współdzielonego.
 */
public class SemaphoreDemo {
    // Zasób współdzielony - licznik
    private static int counter = 0;
    // Semafor binarny do ochrony dostępu do licznika
    private static BinarySemaphore semaphore = new BinarySemaphore(1);
    
    public static void main(String[] args) {
        System.out.println("Demonstracja semafora binarnego");
        
        // Tworzymy i uruchamiamy wątki inkrementujące licznik
        Thread[] threads = new Thread[5];
        for (int i = 0; i < threads.length; i++) {
            threads[i] = new Thread(new IncrementTask(), "Wątek-" + i);
            threads[i].start();
        }
        
        // Czekamy na zakończenie wszystkich wątków
        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        
        System.out.println("Końcowa wartość licznika: " + counter);
    }
    
    /**
     * Zadanie inkrementujące licznik w sposób bezpieczny przy użyciu semafora.
     */
    static class IncrementTask implements Runnable {
        @Override
        public void run() {
            for (int i = 0; i < 1000; i++) {
                try {
                    // Operacja P - próba zablokowania semafora
                    semaphore.P();
                    
                    try {
                        // Sekcja krytyczna - dostęp do zasobu współdzielonego
                        int temp = counter;
                        // Symulacja dłuższej operacji
                        Thread.sleep(1);
                        counter = temp + 1;
                        
                        System.out.println(Thread.currentThread().getName() + 
                                           " inkrementował licznik do " + counter);
                    } finally {
                        // Operacja V - odblokowanie semafora
                        semaphore.V();
                    }
                    
                    // Symulacja pracy poza sekcją krytyczną
                    Thread.sleep(5);
                    
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    System.out.println(Thread.currentThread().getName() + " został przerwany");
                    return;
                }
            }
        }
    }
} 