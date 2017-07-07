#ifndef KIS_WATERCOLOR_BASE_ITEMS_H
#define KIS_WATERCOLOR_BASE_ITEMS_H

#include <KoRTree.h>
#include "kis_splat.h"
#include "kis_wetmap.h"
#include <QTimer>
#include <QObject>

class KisWatercolorBaseItems : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    void update();

public:
    static KisWatercolorBaseItems* instance() {
        static KisWatercolorBaseItems instance;
        return &instance;
    }

    void paint(QPointF pos, qreal radius, KoColor color, int brushType);

private:
    static KisWatercolorBaseItems * p_instance;
    KisWatercolorBaseItems();
    KisWatercolorBaseItems( const KisWatercolorBaseItems& );
    KisWatercolorBaseItems& operator=( KisWatercolorBaseItems& );

    KisWetMap *m_wetMap;
    KoRTree<KisSplat *> m_flowing;
    KoRTree<KisSplat *> m_fixed;
    KoRTree<KisSplat *> m_dried;

    QTimer m_updater;

    KisPaintDeviceSP m_paintDev;
};

#endif // KIS_WATERCOLOR_BASE_ITEMS_H
