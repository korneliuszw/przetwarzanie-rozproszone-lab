import java.util.Random;

/**
 * Klasa reprezentująca producenta, który produkuje towary i umieszcza je w magazynie.
 */
public class Producer implements Runnable {
    private final Warehouse warehouse;
    private final String[] productTypes;
    private final String name;
    private final Random random;

    /**
     * Tworzy nowego producenta.
     * 
     * @param name nazwa producenta
     * @param warehouse magazyn, do którego producent dodaje towary
     * @param productTypes typy produktów, które producent może produkować
     */
    public Producer(String name, Warehouse warehouse, String[] productTypes) {
        this.name = name;
        this.warehouse = warehouse;
        this.productTypes = productTypes;
        this.random = new Random();
    }

    @Override
    public void run() {
        while (!Thread.currentThread().isInterrupted()) {
            try {
                // Losowy czas produkcji
                Thread.sleep(random.nextInt(1000) + 500);
                
                // Losowy typ produktu
                String productType = productTypes[random.nextInt(productTypes.length)];
                
                // Losowa ilość produktu (1-10)
                int quantity = random.nextInt(10) + 1;
                
                boolean added = warehouse.addProduct(productType, quantity);
                
                if (added) {
                    System.out.println(name + " wyprodukował " + quantity + " sztuk produktu " + productType);
                } else {
                    System.out.println(name + " nie mógł dodać " + quantity + " sztuk produktu " + productType + " - brak miejsca w magazynie");
                }
                
                // Wyświetl stan magazynu
                System.out.println("Stan magazynu: " + warehouse.getCurrentOccupancy() + "/" + warehouse.getCapacity());
                
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
    }
} 