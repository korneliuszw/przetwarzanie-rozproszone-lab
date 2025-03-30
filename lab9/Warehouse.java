import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Klasa reprezentująca magazyn, który przechowuje różne typy towarów.
 * Magazyn ma ograniczoną pojemność i zapewnia synchronizowany dostęp
 * dla producentów i konsumentów.
 */
public class Warehouse {
    private final int capacity;
    private int currentOccupancy;
    private final Map<String, Integer> products;
    private final Lock lock;

    /**
     * Tworzy nowy magazyn o określonej pojemności.
     * 
     * @param capacity maksymalna pojemność magazynu
     */
    public Warehouse(int capacity) {
        this.capacity = capacity;
        this.currentOccupancy = 0;
        this.products = new HashMap<>();
        this.lock = new ReentrantLock();
    }

    /**
     * Dodaje produkt do magazynu.
     * 
     * @param productType typ produktu
     * @param quantity ilość produktu
     * @return true jeśli produkt został dodany, false jeśli brak miejsca
     */
    public boolean addProduct(String productType, int quantity) {
        lock.lock();
        try {
            if (currentOccupancy + quantity > capacity) {
                return false;
            }

            products.put(productType, products.getOrDefault(productType, 0) + quantity);
            currentOccupancy += quantity;
            return true;
        } finally {
            lock.unlock();
        }
    }

    /**
     * Pobiera produkt z magazynu.
     * 
     * @param productType typ produktu
     * @param requestedQuantity żądana ilość produktu
     * @return faktycznie pobrana ilość produktu (może być mniejsza niż żądana)
     */
    public int getProduct(String productType, int requestedQuantity) {
        lock.lock();
        try {
            int availableQuantity = products.getOrDefault(productType, 0);
            if (availableQuantity == 0) {
                return 0;
            }

            int actualQuantity = Math.min(availableQuantity, requestedQuantity);
            
            if (actualQuantity == availableQuantity) {
                products.remove(productType);
            } else {
                products.put(productType, availableQuantity - actualQuantity);
            }
            
            currentOccupancy -= actualQuantity;
            return actualQuantity;
        } finally {
            lock.unlock();
        }
    }

    /**
     * Zwraca aktualny stan magazynu.
     * 
     * @return mapa produktów i ich ilości
     */
    public Map<String, Integer> getInventory() {
        lock.lock();
        try {
            return new HashMap<>(products);
        } finally {
            lock.unlock();
        }
    }

    /**
     * Zwraca aktualną zajętość magazynu.
     * 
     * @return aktualna zajętość
     */
    public int getCurrentOccupancy() {
        lock.lock();
        try {
            return currentOccupancy;
        } finally {
            lock.unlock();
        }
    }

    /**
     * Zwraca maksymalną pojemność magazynu.
     * 
     * @return pojemność magazynu
     */
    public int getCapacity() {
        return capacity;
    }
} 