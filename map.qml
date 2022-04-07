import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Rectangle {

    property double oldlat:25.6585
    property double  oldlng:100.3658

    Plugin{
        id:mapPlugin
        name:"osm"
        PluginParameter {
                            name: "osm.mapping.providersrepository.disabled"
                            value: "true"
                        }
                        PluginParameter {
                            name: "osm.mapping.providersrepository.address"
                            value: "http://maps-redirect.qt.io/osm/5.8/satellite"
                        }
    }

    Map
    {
        id :mapView
        anchors.fill: parent
        plugin: mapPlugin
        center: Qtpositioning.coordinate(oldlat,oldlng);
        zoomLevel: 15
    }
    function setCenter(lat,lng){
        mapView.pan(oldlat - lat ,oldlng - lng)
        oldlat=lat
        oldlng=lng;
    }
}
